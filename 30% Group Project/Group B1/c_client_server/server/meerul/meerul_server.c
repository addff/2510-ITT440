#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <pthread.h>

#define TARGET_USER "Meerul"
#define PORT 5004
#define DB_HOST "host.docker.internal"
#define DB_USER "root"
#define DB_PASS "qwerty"
#define DB_NAME "itt440_db"


void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void ensure_user_exists() {
    MYSQL *con = mysql_init(NULL);
    if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0) == NULL) finish_with_error(con);

    char query[256];
    sprintf(query, "SELECT user FROM student_table WHERE user = '%s'", TARGET_USER);
    mysql_query(con, query);
    MYSQL_RES *result = mysql_store_result(con);

    if (mysql_num_rows(result) == 0) {
        sprintf(query, "INSERT INTO student_table (user, points, datetime_stamp) VALUES ('%s', 0, NOW())", TARGET_USER);
        if (mysql_query(con, query)) finish_with_error(con);
        printf("Startup: User '%s' created.\n", TARGET_USER);
    } else {
        printf("Startup: User '%s' already exists.\n", TARGET_USER);
    }

    mysql_free_result(result);
    mysql_close(con);
}

void* auto_increment(void* arg) {
    while(1) {
        sleep(30);
        MYSQL *con = mysql_init(NULL);
        if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0)) {
            char query[256];
            sprintf(query, "UPDATE student_table SET points = points + 1, datetime_stamp = NOW() WHERE user = '%s'", TARGET_USER);
            mysql_query(con, query);
            mysql_close(con);
            printf("Tick: Point added to %s\n", TARGET_USER);
        }
    }
    return NULL;
}

int main() {
    ensure_user_exists();

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, auto_increment, NULL);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("C Server: Monitoring %s on port %d\n", TARGET_USER, PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        MYSQL *con = mysql_init(NULL);
        mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

        char query[256];
        sprintf(query, "SELECT points FROM student_table WHERE user = '%s'", TARGET_USER);
        mysql_query(con, query);
        MYSQL_RES *res = mysql_store_result(con);
        MYSQL_ROW row = mysql_fetch_row(res);

        char response[1024];
        if (row) sprintf(response, "C Server Response | User: %s | Points: %s", TARGET_USER, row[0]);
        else sprintf(response, "Error: %s not found.", TARGET_USER);

        send(new_socket, response, strlen(response), 0);
        mysql_free_result(res);
        mysql_close(con);
        close(new_socket);
    }
    return 0;
}