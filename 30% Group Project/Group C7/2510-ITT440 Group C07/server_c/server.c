#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DB_HOST "mysql-db"
#define DB_USER "root"
#define DB_PASS "adminpass"
#define DB_NAME "socket_db"


void* update_loop(void* arg) {
    const char *target_user = "CUser1"; 

    while(1) {
        MYSQL *conn = mysql_init(NULL);
        if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0)) {
            char query[256];
            
            sprintf(query, "INSERT INTO scores (user, points) VALUES ('%s', 1) "
                           "ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()", 
                           target_user);
            
            if (mysql_query(conn, query)) {
                fprintf(stderr, "C-Server 1 Error: %s\n", mysql_error(conn));
            } else {
                printf("C-Server 1: Points increased for %s\n", target_user);
            }
            mysql_close(conn);
        }
        sleep(30);
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, update_loop, NULL);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = htons(5002) };
    
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("C Server 1 listening on Port 5002 (User: CUser1)...\n");

    while(1) {
        int sock = accept(server_fd, NULL, NULL);
        char buffer[1024] = {0};
        read(sock, buffer, 1024);

        if (strncmp(buffer, "GET_SCORE", 9) == 0) {
            MYSQL *conn = mysql_init(NULL);
            mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
            
            
            char select_query[256];
            sprintf(select_query, "SELECT user, points, datetime_stamp FROM scores WHERE user = 'CUser1'");
            
            mysql_query(conn, select_query);
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            
            char response[1024] = "";
            if (row) {
                sprintf(response, "User: %s | Points: %s | Last Update: %s\n", row[0], row[1], row[2]);
            } else {
                strcpy(response, "Data not found for CUser1\n");
            }

            send(sock, response, strlen(response), 0);
            mysql_free_result(res);
            mysql_close(conn);
        }
        close(sock);
    }
    return 0;
}
