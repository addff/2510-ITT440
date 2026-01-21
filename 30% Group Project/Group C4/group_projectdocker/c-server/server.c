#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 5001

MYSQL *conn;

void* updater_thread(void* arg) {
    while (1) {
        if (mysql_query(conn, "UPDATE points_table SET points = points + 1, last_update = NOW()")) {
            fprintf(stderr, "Update failed: %s\n", mysql_error(conn));
        } else {
            printf("Points updated for all users.\n");
        }
        sleep(30);
    }
    return NULL;
}

int main() {
    printf("Starting C server...\n");

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "mysql-db", "c_server", "cpass",
                           "assignmentdb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    printf("Connected to MySQL successfully!\n");

   
    pthread_t tid;
    pthread_create(&tid, NULL, updater_thread, NULL);


    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        return 1;
    }
    printf("Listening on port %d...\n", PORT);

    while (1) {
        int addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address,
                               (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected!\n");

        char username[64];
        int n = recv(client_fd, username, sizeof(username)-1, 0);
        if (n <= 0) {
            printf("No username received.\n");
            close(client_fd);
            continue;
        }
        username[n] = '\0';
        printf("Client requested user: %s\n", username);

        char select_query[256];
        snprintf(select_query, sizeof(select_query),
                 "SELECT points, last_update FROM points_table WHERE user='%s'",
                 username);

        if (mysql_query(conn, select_query) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer),
                         "Total %s points: %s (updated at %s)\n",
                         username, row[0], row[1]);
                send(client_fd, buffer, strlen(buffer), 0);
                printf("Sent to client: %s", buffer);
            }
            mysql_free_result(res);
        } else {
            fprintf(stderr, "Select failed: %s\n", mysql_error(conn));
        }

        close(client_fd);
    }

    mysql_close(conn);
    close(server_fd);
    return 0;
}