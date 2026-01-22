#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <sys/socket.h>

//define for database phpmyadmin connection
const char *DB_HOST, *DB_USER, *DB_PASS, *DB_NAME, *USER_NAME;
int SERVER_PORT;

//update points every 30 seconds
void *update_points(void *arg) {
    while (1) {
        MYSQL *conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
            printf("DB not ready!, retrying...\n");
            sleep(5);
            continue;
        }

        char query[256];
        snprintf(query, sizeof(query),
                 "UPDATE Star_point "
                 "SET points = points + 1, datetime_stamp = NOW() "
                 "WHERE user = '%s'", USER_NAME);

        if (mysql_query(conn, query) == 0) {
            printf("Point: %s\n", USER_NAME);
        } else {
            printf("Error: %s\n", mysql_error(conn));
        }

        mysql_close(conn);
        sleep(30);
    }
}

// client ask request
void handle_client(int client_sock) {
    char buffer[100];
    int r = recv(client_sock, buffer, sizeof(buffer)-1, 0);

    if (r > 0) {
        buffer[r] = '\0';

        if (strcmp(buffer, "GET") == 0) {
            MYSQL *conn = mysql_init(NULL);
            mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);

            char query[256];
            snprintf(query, sizeof(query),
                     "SELECT points, datetime_stamp "
                     "FROM Star_point WHERE user='%s'", USER_NAME);

            mysql_query(conn, query);
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);

            char reply[256];
            snprintf(reply, sizeof(reply),
                     "User: %s | Points: %s | Timestamp: %s",
                     USER_NAME, row[0], row[1]);

            send(client_sock, reply, strlen(reply), 0);

            mysql_free_result(res);
            mysql_close(conn);
        }
    }
    close(client_sock);
}

int main() {

    DB_HOST = getenv("DB_HOST");
    DB_USER = getenv("DB_USER");
    DB_PASS = getenv("DB_PASS");
    DB_NAME = getenv("DB_NAME");
    USER_NAME = getenv("USER_NAME");   
    SERVER_PORT = atoi(getenv("SERVER_PORT")); 

    pthread_t updater_thread;
    pthread_create(&updater_thread, NULL, update_points, NULL);

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_sock, 5);

    printf("CClient_Nad run on port %d\n", SERVER_PORT);

    while (1) {
        int client_sock = accept(server_sock, NULL, NULL);
        handle_client(client_sock);
    }
}

