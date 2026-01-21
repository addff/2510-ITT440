#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define PORT 5004

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    struct hostent *hp = gethostbyname("host.docker.internal");
    if (hp == NULL) inet_pton(AF_INET, "172.17.0.1", &serv_addr.sin_addr);
    else memcpy(&serv_addr.sin_addr, hp->h_addr_list[0], hp->h_length);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    send(sock, "fetch", 5, 0);
    read(sock, buffer, 1024);
    
    printf("----------------------------------------\n");
    printf("%s\n", buffer);
    printf("----------------------------------------\n");

    close(sock);
    return 0;
}