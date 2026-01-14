#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h> // For gethostbyname

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    struct hostent *server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Resolve the hostname "server_c"
    server = gethostbyname("nabil-server"); 
    if (server == NULL) {
        fprintf(stderr, "Error: Could not resolve hostname\n");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5001); // Match the server port!
    
    // Copy the resolved IP address into the sockaddr structure
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    int bytes_read = read(sock, buffer, 1024);
    if (bytes_read > 0) {
        printf("Message from C Server:\n%s\n", buffer);
    } else {
        printf("Connected, but no data received.\n");
    }

    close(sock);
    return 0;
}
