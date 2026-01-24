#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8084
#define DB_HOST "database"
#define DB_USER "root"
#define DB_PASS "rootpassword"
#define DB_NAME "socket_db"

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP string to binary
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid IP address");
        close(sock);
        return 1;
    }

    // 3. Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server %s:%d\n", SERVER_IP, PORT);

    // 4. Send request to server
    char message[] = "GET_POINTS";
    send(sock, message, strlen(message), 0);
    printf("Request sent: %s\n", message);

    // 5. Receive response from server (database output)
    int bytes = read(sock, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Server response: %s\n", buffer);
    }

    // 6. Close socket
    close(sock);
    return 0;
}
