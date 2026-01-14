//New Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 5009 
#define BUFFER_SIZE 1024

int main() {
    setbuf(stdout, NULL);
    printf("=== SERVER STARTING ===\n");
    printf("Listening on port %d\n", SERVER_PORT);
    fflush(stdout);
    
    char request[BUFFER_SIZE];
    srand(time(NULL));
    int listenfd;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    socklen_t clilen = sizeof(cliaddr);
    time_t last_update = 0;

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_family = AF_INET; 

    // Set socket timeout to 1 second
    struct timeval tv;
    tv.tv_sec = 1;  // 1 second timeout
    tv.tv_usec = 0;
    setsockopt(listenfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    
    // Bind server address to socket descriptor
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while (1) {
        time_t now = time(NULL);
        
        // Update record every 30 seconds (independent of client requests)
        if (difftime(now, last_update) >= 30) {
            printf("\n[SERVER] Auto-updating database (30 seconds elapsed)...\n");
            fflush(stdout);
            
            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                char query[512];
                sprintf(query, "INSERT INTO points_table (user, points, datetime_stamp) "
                               "VALUES ('FATHU_C', 1, NOW()) "
                               "ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()");
                mysql_query(conn, query);
                mysql_close(conn);
                last_update = now;
                printf("[SERVER] Database updated! Points incremented.\n");
                fflush(stdout);
            }
        }
        
        // Try to receive client request (with 1 second timeout)
        clilen = sizeof(cliaddr);
        memset(&cliaddr, 0, sizeof(cliaddr));
        memset(request, 0, sizeof(request));
        
        int n = recvfrom(listenfd, request, sizeof(request) - 1, 0,
                        (struct sockaddr*)&cliaddr, &clilen);
        
        if (n < 0) {
            // Timeout or error - just continue loop to check time again
            continue;
        }
        
        if (n > 0) {
            request[n] = '\0';
            printf("\n[SERVER] Received request from client: %s\n", request);
            fflush(stdout);
            
            // Connect to MySQL and send response
            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                mysql_query(conn, "SELECT user, points, datetime_stamp FROM points_table WHERE user='FATHU_C'");
                MYSQL_RES *res = mysql_store_result(conn);
                MYSQL_ROW row = mysql_fetch_row(res);
                
                if (row) {
                    char response[BUFFER_SIZE];
                    snprintf(response, sizeof(response), 
                             "User: %s\nPoints: %s\nTimestamp: %s\n", 
                             row[0], row[1], row[2]);         
                    
                    printf("[SERVER] Sending to client:\n%s", response);
                    fflush(stdout);
                    
                    sendto(listenfd, response, strlen(response), 0, 
                          (struct sockaddr*)&cliaddr, clilen);
                }
                mysql_free_result(res);
                mysql_close(conn);
            }
        }      
    }
    return 0;
}

//old code
/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 5009 
#define BUFFER_SIZE 1024

int main() {
    setbuf(stdout, NULL);  // Disable buffering
    printf("=== SERVER STARTING ===\n");
    printf("Listening on port %d\n", SERVER_PORT);
    fflush(stdout);
    
    char request[BUFFER_SIZE];
    srand(time(NULL));
    int listenfd, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    socklen_t clilen = sizeof(cliaddr);
    time_t last_update = 0;

    //Create a UDP Socket//
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_family = AF_INET; 

    
    //Bind server address to socket descriptor
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));


    while (1) {
        clilen = sizeof(cliaddr);
        memset(&cliaddr, 0, sizeof(cliaddr));
        memset(request, 0, sizeof(request));
        printf("\n[SERVER] Waiting for client request...\n");
        fflush(stdout);
        int n = recvfrom(listenfd, request, sizeof(request) - 1, 0,(struct sockaddr*)&cliaddr, &clilen);
        printf("[SERVER] recvfrom returned: %d\n", n);
        fflush(stdout);
        
        if (n < 0) {
                  perror("recvfrom error");
                  continue;
         }
         
        time_t now = time(NULL);
         
        // Update record every 30 seconds 
        if (difftime(now, last_update) >= 30) {
            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                // Points must increase every time updated 
                char query[512];
                sprintf(query, "INSERT INTO points_table (user, points, datetime_stamp) "
                               "VALUES ('FATHU_C', 1, NOW()) "
                               "ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()");
                mysql_query(conn, query);
                mysql_close(conn);
                last_update = now;
            }
        }
            
            if (n > 0) {
                 request[n] = '\0';  // Null-terminate
                 printf("Received request from client: %s\n", request);
                 fflush(stdout);
                 
                 // Now connect to MySQL and send response
                  MYSQL *conn = mysql_init(NULL);
                  if (mysql_real_connect(conn, "mysql", "root", "rootpassword", "pointsdb", 3306, NULL, 0)) {
                      // Accessing latest point and timestamp 
                      mysql_query(conn, "SELECT user, points, datetime_stamp FROM points_table WHERE user='FATHU_C'");
                      MYSQL_RES *res = mysql_store_result(conn);
                      MYSQL_ROW row = mysql_fetch_row(res);
                      
                      if (row) {
                          char response[BUFFER_SIZE];
                          
                          // Format: User, Points, Timestamp[cite: 33, 42]
                          snprintf(response, sizeof(response), 
                                   "User: %s\nPoints: %s\nTimestamp: %s\n", 
                                   row[0], row[1], row[2]);         
                          
                          printf("Sending to client:\n%s\n", response);
                          fflush(stdout);
                                   
                          sendto(listenfd, response, strlen(response), 0, (struct sockaddr*)&cliaddr, clilen);
                      }
                      mysql_free_result(res);
                      mysql_close(conn);
                  }
            }      
    }
    return 0;

}
*/
