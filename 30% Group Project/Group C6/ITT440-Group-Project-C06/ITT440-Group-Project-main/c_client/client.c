#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>       // for gethostbyname
#include <sys/socket.h>

#define SERVER_NAME "c-server"  // Docker Compose service name
#define SERVER_PORT 5003
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *he = gethostbyname(SERVER_NAME);;
    char buffer[BUFFER_SIZE] = {0};

    // Resolve service name to IP
    he = gethostbyname(SERVER_NAME);
    if (he == NULL) {
        fprintf(stderr, "Failed to resolve host: %s\n", SERVER_NAME);
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    const char *request = "GET_POINTS";
    send(sock, request, strlen(request), 0);

    // Receive server response
    int valread = read(sock, buffer, BUFFER_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0'; // null-terminate
        printf("Server response: %s\n", buffer);
    } else {
        printf("No response from server.\n");
    }

    close(sock);
    return 0;
}
