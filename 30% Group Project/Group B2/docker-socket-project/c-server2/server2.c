#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <time.h>

#define PORT 8084
#define DB_HOST "database"
#define DB_USER "root"
#define DB_PASS "rootpassword"
#define DB_NAME "socket_db"

void update_database_points(const char* username) {
    MYSQL *conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }
    
    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE user_points SET points = points + 1, datetime_stamp = NOW() WHERE user = '%s'",
             username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Update failed: %s\n", mysql_error(conn));
    } else {
        printf("Updated points for %s\n", username);
    }
    
    mysql_close(conn);
}

void get_latest_points(const char* username, char* buffer, size_t buffer_size) {
    MYSQL *conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        snprintf(buffer, buffer_size, "Database connection failed");
        return;
    }
    
    char query[256];
    snprintf(query, sizeof(query),
             "SELECT points, datetime_stamp FROM user_points WHERE user = '%s'",
             username);
    
    if (mysql_query(conn, query) == 0) {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row) {
                snprintf(buffer, buffer_size, "User: %s, Points: %s, Last Updated: %s", 
                         username, row[0], row[1]);
            }
            mysql_free_result(result);
        }
    }
    
    mysql_close(conn);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("C Server listening on port %d\n", PORT);
    
    // Auto-update points every 30 seconds
    pid_t pid = fork();
    if (pid == 0) {
        // Child process for periodic updates
        while(1) {
            sleep(30);
            update_database_points("c_user2");
        }
    }
    
    // Main process for handling client connections
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        // Read client request
        read(new_socket, buffer, 1024);
        
        if (strstr(buffer, "GET_POINTS") != NULL) {
            char response[1024];
            get_latest_points("c_user2", response, sizeof(response));
            send(new_socket, response, strlen(response), 0);
        }
        
        close(new_socket);
    }
    
    return 0;
}
