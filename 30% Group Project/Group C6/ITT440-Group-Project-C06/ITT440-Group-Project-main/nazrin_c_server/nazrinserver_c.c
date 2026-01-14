#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 5004 
#define BUFFER_SIZE 1024

int main() {
    srand(time(NULL));
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    time_t last_update = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    while (1) {
        time_t now = time(NULL);

        // Update record every 30 seconds 
        if (difftime(now, last_update) >= 30) {
            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                // Points must increase every time updated 
                char query[512];
                sprintf(query, "INSERT INTO points_table (user, points, datetime_stamp) "
                               "VALUES ('nazrin_user', 1, NOW()) "
                               "ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()");

                if (mysql_query(conn, query)) {
                    fprintf(stderr, "Update Error: %s\n", mysql_error(conn));
                } else {
                    printf("Database updated for nazrin_user at %ld\n", now);
                }
                mysql_query(conn, query);
                mysql_close(conn);
                last_update = now;
            }
        }

        // Check for Client Connections (Non-blocking)
        struct timeval tv = {0, 1000}; 
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        
        if (select(server_fd + 1, &readfds, NULL, NULL, &tv) > 0) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                // Accessing latest point and timestamp 
                mysql_query(conn, "SELECT user, points, datetime_stamp FROM points_table WHERE user='nazrin_user'");
                MYSQL_RES *res = mysql_store_result(conn);
                MYSQL_ROW row = mysql_fetch_row(res);
                
                if (row) {
                    // Generate a separate random number for this specific request
                    int lucky_number = rand() % 1000;
                    char response[BUFFER_SIZE];
                    
                    snprintf(response, sizeof(response), 
                             "User: %s\nPoints: %s\nTimestamp: %s\nRandom Value: %d\n", 
                             row[0], row[1], row[2], lucky_number);
                    
                    send(new_socket, response, strlen(response), 0);
                }
                mysql_free_result(res);
                mysql_close(conn);
            }
            close(new_socket);
        }
    }
    return 0;
}
