#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define SERVER_HOST "c-server-container"
#define SERVER_PORT 5002

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct hostent *he;
    char *message = "GET_SCORE";
    char buffer[2048] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    he = gethostbyname(SERVER_HOST);
    if (he == NULL) {
        printf("Could not resolve hostname: %s\n", SERVER_HOST);
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    memcpy(&serv_addr.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed. Is the C-Server running?\n");
        return -1;
    }

    send(sock, message, strlen(message), 0);
    printf("Request sent to C Server...\n");
    
    read(sock, buffer, 2048);
    printf("\n--- C Server Response ---\n%s", buffer);

    close(sock);
    return 0;
}
