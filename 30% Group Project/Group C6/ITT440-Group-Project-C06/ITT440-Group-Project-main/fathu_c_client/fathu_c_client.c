#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define SERVER_NAME "fathu-c-server"
#define SERVER_PORT 5009

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    int ans;
    struct hostent *he;
    char buffer[1024] = {0};

    // Resolve specific server container name [cite: 26, 46]
    he = gethostbyname(SERVER_NAME);
    if (he == NULL) return 1;
    
    
    while(1){
    memset(buffer, 0, sizeof(buffer));
    //clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_family = AF_INET;
    memcpy(&servaddr.sin_addr, he->h_addr_list[0], he ->h_length);
    
    //Create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

      // Ask the server for the latest point [cite: 49]
      if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0) {
          printf("Ask fathu's current point? (1 = yes, 0 = No)\n");
          
          int c;
          
          scanf("%d", &ans);
          
          while (getchar() != '\n');
          
            if (ans == 1){
                //Sending request
                char request[] = "GET_POINTS";  //  Send some request
                sendto(sockfd, request, strlen(request), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
                
                //Receive response
                  int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,(struct sockaddr*)NULL, NULL);
                    if (bytes_received > 0) {
                        printf("%s", buffer); 
                        fflush(stdout);
                    }
            }else if (ans == 0){
                printf("Ok!\n");
            
            }else {
              printf("You have entered a wrong format of input!\n");
            }
        
      }

      close(sockfd);
      sleep(10);
    }
    
    return 0;
}