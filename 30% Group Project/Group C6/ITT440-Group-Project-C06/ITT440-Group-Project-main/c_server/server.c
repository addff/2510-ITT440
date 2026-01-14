#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERVER_PORT 5003
#define BUFFER_SIZE 1024

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *db_host = "mysql";
    const char *db_user = "root";
    const char *db_pass = "rootpassword";
    const char *db_name = "pointsdb";

    // --- Create TCP server ---
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Allow reuse of address
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
    address.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("C server listening on port %d...\n", SERVER_PORT);

    // --- Main loop ---
    while (1) {
        // Update points in MySQL
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 3306, NULL, 0)) {
            fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        } else {
            char query[256];
            time_t now = time(NULL);
            snprintf(query, sizeof(query),
                     "INSERT INTO points_table (user, points, datetime_stamp) "
                     "VALUES('c_user', 1, FROM_UNIXTIME(%ld)) "
                     "ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = FROM_UNIXTIME(%ld);",
                     now, now);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "MySQL update failed: %s\n", mysql_error(conn));
            } else {
                printf("Updated points for c_user\n");
            }
            mysql_close(conn);
        }

        // --- Accept client connections (non-blocking for simplicity) ---
        fd_set readfds;
        struct timeval tv;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);

        tv.tv_sec = 0;
        tv.tv_usec = 0; // non-blocking accept

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &tv);
        if (activity > 0 && FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            if (new_socket < 0) {
                perror("accept");
                continue;
            }

            // Query latest points for c_user
            conn = mysql_init(NULL);
            if (!mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 3306, NULL, 0)) {
                char *msg = "Error connecting to DB\n";
                send(new_socket, msg, strlen(msg), 0);
            } else {
                if (mysql_query(conn, "SELECT points, datetime_stamp FROM points_table WHERE user='c_user';")) {
                    char *msg = "Query failed\n";
                    send(new_socket, msg, strlen(msg), 0);
                } else {
                    res = mysql_store_result(conn);
                    if ((row = mysql_fetch_row(res)) != NULL) {
                        char msg[BUFFER_SIZE];
                        snprintf(msg, sizeof(msg), "User: c_user, Points: %s, Last update: %s\n", row[0], row[1]);
                        send(new_socket, msg, strlen(msg), 0);
                    }
                    mysql_free_result(res);
                }
                mysql_close(conn);
            }

            close(new_socket);
        }

        sleep(30); // update points every 30s
    }

    return 0;
}
