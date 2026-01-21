#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <mysql/mysql.h>

#define PORT 5001
#define DB_HOST "mysql_db"
#define DB_USER "root"
#define DB_PASS "root123"
#define DB_NAME "itt440_db"

MYSQL *conn;

void update_database() {
    char query[256];
    sprintf(query, "UPDATE user_points SET points = points + 1, datetime_stamp = NOW() WHERE user = 'ahmad'");
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Database update failed: %s\n", mysql_error(conn));
    } else {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char time_buffer[26];
        strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("[%s] Ahmad's points updated\n", time_buffer);
    }
}

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        if (strstr(buffer, "GET_POINTS") != NULL) {
            char query[256];
            sprintf(query, "SELECT points FROM user_points WHERE user = 'ahmad'");
            
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                char *response = "Error getting points";
                send(client_socket, response, strlen(response), 0);
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result != NULL) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    char response[256];
                    sprintf(response, "Ahmad Points: %s", row[0]);
                    send(client_socket, response, strlen(response), 0);
                    mysql_free_result(result);
                }
            }
        } else {
            char *response = "Send GET_POINTS to get points";
            send(client_socket, response, strlen(response), 0);
        }
    }
    
    close(client_socket);
}

int main() {
    printf("C Server (Ahmad) starting on port %d\n", PORT);
    
    // Connect to MySQL
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
        printf("Will retry in 5 seconds...\n");
        sleep(5);
        
        // Retry connection
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
            fprintf(stderr, "Database connection failed again: %s\n", mysql_error(conn));
            return 1;
        }
    }
    printf("Connected to database\n");
    
    // Socket setup
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        return 1;
    }
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }
    
    printf("Server listening on port %d\n", PORT);
    
    time_t last_update = time(NULL);
    
    while (1) {
        // Update every 30 seconds
        if (difftime(time(NULL), last_update) >= 30) {
            update_database();
            last_update = time(NULL);
        }
        
        // Handle clients with timeout
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        
        struct timeval timeout = {1, 0}; // 1 second timeout
        
        if (select(server_fd + 1, &readfds, NULL, NULL, &timeout) > 0) {
            int client_socket = accept(server_fd, NULL, NULL);
            if (client_socket >= 0) {
                handle_client(client_socket);
            }
        }
    }
    
    mysql_close(conn);
    return 0;
}