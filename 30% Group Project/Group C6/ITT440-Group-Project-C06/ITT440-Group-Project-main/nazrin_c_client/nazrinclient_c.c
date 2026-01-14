#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_NAME "nazrinserver_c"
#define SERVER_PORT 5004

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *he;
    char buffer[1024] = {0};

    // Resolve specific server container name [cite: 26, 46]
    he = gethostbyname(SERVER_NAME);
    if (he == NULL) return 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Ask the server for the latest point [cite: 49]
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
        int bytes_received = read(sock, buffer, 1024);
        if (bytes_received > 0) {
            printf("%s", buffer); 
            fflush(stdout);
        }
    }

    close(sock);
    return 0;
}
