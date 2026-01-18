#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 6002

// Database configuration
const char *DB_HOST;
const char *DB_USER;
const char *DB_PASSWORD;
const char *DB_NAME;
const char *USER_NAME;
int SERVER_PORT;

int running = 1;
int update_paused = 0;  // Global pause flag

// Database connection
MYSQL* connect_to_database() {
    MYSQL *conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    
    return conn;
}

// Auto-update thread function
void* update_user_points(void *arg) {
    while (running) {
        // Check if updates are paused
        if (!update_paused) {
            MYSQL *conn = connect_to_database();
            if (conn != NULL) {
                char query[256];
                snprintf(query, sizeof(query), 
                        "UPDATE user_tracking SET points = points + 10, datetime_stamp = NOW() WHERE user = '%s'", 
                        USER_NAME);
                
                if (mysql_query(conn, query)) {
                    fprintf(stderr, "UPDATE failed: %s\n", mysql_error(conn));
                } else {
                    // Fetch updated values
                    snprintf(query, sizeof(query), 
                            "SELECT user, points, datetime_stamp FROM user_tracking WHERE user = '%s'", 
                            USER_NAME);
                    
                    if (mysql_query(conn, query) == 0) {
                        MYSQL_RES *result = mysql_store_result(conn);
                        if (result != NULL) {
                            MYSQL_ROW row = mysql_fetch_row(result);
                            if (row) {
                                time_t now = time(NULL);
                                printf("[%s] Updated %s: Points=%s, Time=%s\n", 
                                       ctime(&now), row[0], row[1], row[2]);
                            }
                            mysql_free_result(result);
                        }
                    }
                }
                mysql_close(conn);
            }
        } else {
            time_t now = time(NULL);
            char time_str[26];
            ctime_r(&now, time_str);
            time_str[24] = '\0';  // Remove newline
            printf("[%s] Updates paused for %s\n", time_str, USER_NAME);
        }
        sleep(30);  // Update every 30 seconds
    }
    return NULL;
}

// Get user data from database
int get_user_data(char *buffer, size_t buffer_size) {
    MYSQL *conn = connect_to_database();
    if (conn == NULL) {
        snprintf(buffer, buffer_size, "Database connection error");
        return -1;
    }
    
    char query[256];
    snprintf(query, sizeof(query), 
            "SELECT user, points, datetime_stamp FROM user_tracking WHERE user = '%s'", 
            USER_NAME);
    
    if (mysql_query(conn, query)) {
        snprintf(buffer, buffer_size, "Query error: %s", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }
    
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        snprintf(buffer, buffer_size, "Store result error");
        mysql_close(conn);
        return -1;
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        snprintf(buffer, buffer_size, "User: %s | Points: %s | Last Update: %s", 
                row[0], row[1], row[2]);
    } else {
        snprintf(buffer, buffer_size, "No data found");
    }
    
    mysql_free_result(result);
    mysql_close(conn);
    return 0;
}

// Handle client connection
void* handle_client(void *arg) {
    int client_sock = *(int*)arg;
    free(arg);
    
    char buffer[BUFFER_SIZE];
    
    printf("Client connected\n");
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received <= 0) {
            printf("Client disconnected\n");
            break;
        }
        
        buffer[bytes_received] = '\0';
        
        // Remove newline if present
        char *newline = strchr(buffer, '\n');
        if (newline) *newline = '\0';
        
        printf("Received request: %s\n", buffer);
        
        if (strcasecmp(buffer, "quit") == 0) {
            printf("Client requested quit\n");
            break;
        } else if (strcasecmp(buffer, "get_data") == 0) {
            char response[BUFFER_SIZE];
            get_user_data(response, BUFFER_SIZE);
            send(client_sock, response, strlen(response), 0);
        } else {
            const char *msg = "Invalid command. Use 'get_data' or 'quit'";
            send(client_sock, msg, strlen(msg), 0);
        }
    }
    
    close(client_sock);
    return NULL;
}

// HTTP control server thread
void* control_server(void *arg) {
    int control_port = SERVER_PORT + 1000;  // 7002 for server2.c
    int control_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (control_sock < 0) {
        perror("Control socket creation failed");
        return NULL;
    }
    
    int opt = 1;
    setsockopt(control_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in control_addr;
    memset(&control_addr, 0, sizeof(control_addr));
    control_addr.sin_family = AF_INET;
    control_addr.sin_addr.s_addr = INADDR_ANY;
    control_addr.sin_port = htons(control_port);
    
    if (bind(control_sock, (struct sockaddr*)&control_addr, sizeof(control_addr)) < 0) {
        perror("Control bind failed");
        close(control_sock);
        return NULL;
    }
    
    if (listen(control_sock, 5) < 0) {
        perror("Control listen failed");
        close(control_sock);
        return NULL;
    }
    
    printf("Control server started on port %d\n", control_port);
    
    while (running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(control_sock, (struct sockaddr*)&client_addr, &client_len);
        
        if (client_sock < 0) continue;
        
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        
        // Simple HTTP-like parsing
        if (strstr(buffer, "POST /toggle") != NULL) {
            update_paused = !update_paused;
            const char *status = update_paused ? "paused" : "active";
            char response[256];
            snprintf(response, sizeof(response),
                    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"status\":\"%s\"}", status);
            send(client_sock, response, strlen(response), 0);
            printf("[Control] Updates %s for %s\n", status, USER_NAME);
        } else if (strstr(buffer, "POST /status") != NULL) {
            const char *status = update_paused ? "paused" : "active";
            char response[256];
            snprintf(response, sizeof(response),
                    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"status\":\"%s\"}", status);
            send(client_sock, response, strlen(response), 0);
        }
        
        close(client_sock);
    }
    
    close(control_sock);
    return NULL;
}

int main() {
    // Get environment variables
    DB_HOST = getenv("DB_HOST") ? getenv("DB_HOST") : "database";
    DB_USER = getenv("DB_USER") ? getenv("DB_USER") : "dbuser";
    DB_PASSWORD = getenv("DB_PASSWORD") ? getenv("DB_PASSWORD") : "dbpassword";
    DB_NAME = getenv("DB_NAME") ? getenv("DB_NAME") : "network_project";
    USER_NAME = getenv("USER_NAME") ? getenv("USER_NAME") : "Faiz";
    SERVER_PORT = getenv("SERVER_PORT") ? atoi(getenv("SERVER_PORT")) : DEFAULT_PORT;
    
    printf("C Server starting...\n");
    printf("Managing user: %s\n", USER_NAME);
    printf("Port: %d\n", SERVER_PORT);
    
    // Wait for database to be ready
    sleep(5);
    
    // Create socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    // Bind socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen
    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server started on 0.0.0.0:%d\n", SERVER_PORT);
    
    // Start auto-update thread
    pthread_t update_thread;
    if (pthread_create(&update_thread, NULL, update_user_points, NULL) != 0) {
        perror("Failed to create update thread");
        exit(EXIT_FAILURE);
    }
    pthread_detach(update_thread);
    
    // Start control server thread
    pthread_t control_thread;
    if (pthread_create(&control_thread, NULL, control_server, NULL) != 0) {
        perror("Failed to create control thread");
        exit(EXIT_FAILURE);
    }
    pthread_detach(control_thread);
    
    // Accept client connections
    while (running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        
        if (*client_sock < 0) {
            perror("Accept failed");
            free(client_sock);
            continue;
        }
        
        // Create thread to handle client
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, handle_client, client_sock) != 0) {
            perror("Failed to create client thread");
            close(*client_sock);
            free(client_sock);
            continue;
        }
        pthread_detach(client_thread);
    }
    
    close(server_sock);
    return 0;
}
