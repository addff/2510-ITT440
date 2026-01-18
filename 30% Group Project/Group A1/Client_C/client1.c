#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #ifdef _MSC_VER
        #pragma comment(lib, "ws2_32.lib")
    #endif
    #define close closesocket
    typedef int socklen_t;
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
#endif

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 6001

const char *SERVER_HOST;
int SERVER_PORT;

int main() {
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
#endif

    // Get environment variables
    SERVER_HOST = getenv("SERVER_HOST") ? getenv("SERVER_HOST") : "server_c1";
    SERVER_PORT = getenv("SERVER_PORT") ? atoi(getenv("SERVER_PORT")) : DEFAULT_PORT;
    
    printf("C Client starting...\n");
    printf("Connecting to server: %s:%d\n", SERVER_HOST, SERVER_PORT);
    
    // Wait for server to be ready
    sleep(10);
    
    int sock = -1;
    
    while (1) {
        // Create socket if not connected
        if (sock < 0) {
            printf("Attempting to connect to server...\n");
            
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) {
                perror("Socket creation failed");
                sleep(5);
                continue;
            }
            
            // Resolve hostname
            struct hostent *server = gethostbyname(SERVER_HOST);
            if (server == NULL) {
                fprintf(stderr, "ERROR: No such host: %s\n", SERVER_HOST);
                close(sock);
                sock = -1;
                sleep(5);
                continue;
            }
            
            struct sockaddr_in server_addr;
            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
            server_addr.sin_port = htons(SERVER_PORT);
            
            // Connect to server
            if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                perror("Connection failed");
                close(sock);
                sock = -1;
                printf("Retrying in 5 seconds...\n");
                sleep(5);
                continue;
            }
            
            printf("Connected to server %s:%d\n", SERVER_HOST, SERVER_PORT);
        }
        
        // Send request
        time_t now = time(NULL);
        printf("\n[%s] Requesting data from server...\n", ctime(&now));
        
        const char *request = "get_data";
        if (send(sock, request, strlen(request), 0) < 0) {
            perror("Send failed");
            close(sock);
            sock = -1;
            printf("Reconnecting...\n");
            sleep(5);
            continue;
        }
        
        // Receive response
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received <= 0) {
            printf("Server disconnected\n");
            close(sock);
            sock = -1;
            printf("Reconnecting...\n");
            sleep(5);
            continue;
        }
        
        buffer[bytes_received] = '\0';
        printf("Response: %s\n", buffer);
        
        // Wait 10 seconds before next request
        sleep(10);
    }
    
    if (sock >= 0) {
        close(sock);
    }

#ifdef _WIN32
    WSACleanup();
#endif
    
    return 0;
}
