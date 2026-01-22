#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

const char* get_env_or_default(const char* env_var, const char* default_val) {
    const char* val = getenv(env_var);
    return val ? val : default_val;
}

int main() {

    const char *server_host = get_env_or_default("SERVER_HOST", "server-c2");
    const char *server_port_str = get_env_or_default("SERVER_PORT", "5002");
    int server_port = atoi(server_port_str);

//waiting message 
    printf("CClient_Nad starting..\n");
    printf("connect to: %s\n", server_host);

    printf("Wait for server..\n");
    sleep(30);

    while (1) {
    
    //define variable

        int sockfd;
        struct sockaddr_in server_addr;
        char buffer[256] = {0};

//create socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Socket creation failed!");
            sleep(30);
            continue;
        }

//set server info
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);

        struct hostent *he = gethostbyname(server_host);
        if (he == NULL) {
            printf("Resolved failed: %s\n", server_host);
            close(sockfd);
            sleep(30);
            continue;
        }

        memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

        printf("Connect to %s: ", server_host);
        fflush(stdout);

        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            printf("Failed\n");
            perror("Connection is failed!");
            close(sockfd);
            sleep(30);
            continue;
        }

        printf("Connection Success!\n");

        const char *request = "GET";
        send(sockfd, request, strlen(request), 0);
        //printf("Sent: %s\n", request);

        int bytes_received = recv(sockfd, buffer, sizeof(buffer)-1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("%s\n", buffer);
        }

        close(sockfd);

        printf("Wait for 30 seconds for next request\n\n");
        sleep(30);
    }

    return 0;
}

