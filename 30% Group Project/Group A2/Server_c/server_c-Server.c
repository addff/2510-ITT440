#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>

MYSQL *db_connect() {
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "db", "root", "root", "attendance_db", 0, NULL, 0);
    return conn;
}

int main() {
    MYSQL *conn = db_connect();
    while (1) {
        mysql_query(conn,
            "UPDATE attendance SET points=points+1, datetime_stamp=NOW() WHERE user='student_c'");
        printf("[C SERVER] updated\n");
        sleep(30);
    }
    return 0;
}
