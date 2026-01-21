#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_HOST "c-server"
#define SERVER_PORT 5001

void print_table(const char *username, const char *points, const char *timestamp) {
    printf("\n+----------------+----------------+-------------------------+\n");
    printf("|     User       |     Points     |        Last Update      |\n");
    printf("+----------------+----------------+-------------------------+\n");
    printf("| %-14s | %-14s | %-23s |\n", username, points, timestamp);
    printf("+----------------+----------------+-------------------------+\n\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <client_id>\n", argv[0]);
        return 1;
    }

    char *client_id = argv[1];
    char buffer[1024];

    while (1) {
        struct hostent *he = gethostbyname(SERVER_HOST);
        if (he == NULL) {
            perror("Hostname resolution failed");
            return 1;
        }

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            return 1;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connection to server failed");
            close(sock);
            return 1;
        }

        send(sock, client_id, strlen(client_id), 0);

        int n = read(sock, buffer, sizeof(buffer)-1);
        if (n > 0) {
            buffer[n] = '\0';

            // Expected format: "Total user_c points: 427 (updated at 2026-01-14 09:07:34)"
            char user[64], points[64], timestamp[128];
            sscanf(buffer, "Total %s points: %s (updated at %[^\n])", user, points, timestamp);

            print_table(user, points, timestamp);
        } else {
            printf("No response from server.\n");
        }

        close(sock);

        char choice[10];
        printf("Do you want to ask again? (y/n): ");
        if (fgets(choice, sizeof(choice), stdin) == NULL) break;
        if (choice[0] != 'y' && choice[0] != 'Y') {
            printf("Closing client...\n");
            break;
        }
    }

    return 0;
}