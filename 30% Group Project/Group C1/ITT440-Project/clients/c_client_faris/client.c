#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>

#define SERVER_NAME "c_server_faris"
#define SERVER_PORT 5002
#define MAX_ACTIVITIES 10
#define UPDATE_INTERVAL 30

// Activity log structure
typedef struct {
    char message[70];
    int valid;
} Activity;

Activity activity_log[MAX_ACTIVITIES];
int activity_count = 0;
int current_points = 631;
int update_number = 1;

// Function to get current time for display
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (t) {
        snprintf(buffer, size, "%04d-%02d-%02d %02d:%02d:%02d",
                 t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                 t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        strcpy(buffer, "2026-01-20 00:00:00");
    }
}

// Function to get time for activity logs
void get_time_str(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (t) {
        snprintf(buffer, size, "%02d:%02d:%02d",
                 t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        strcpy(buffer, "00:00:00");
    }
}

// Add activity to log
void add_activity(const char *format, ...) {
    char time_str[10];
    get_time_str(time_str, sizeof(time_str));
    
    char message[50];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Format the final activity string
    snprintf(activity_log[activity_count % MAX_ACTIVITIES].message, 
             sizeof(activity_log[0].message), 
             "• [%s] %s", time_str, message);
    activity_log[activity_count % MAX_ACTIVITIES].valid = 1;
    activity_count++;
    
    if (activity_count > 1000) {
        activity_count = MAX_ACTIVITIES;
    }
}

// Function to print a NEW monitor display with PERFECT alignment
void print_new_monitor(const char *status) {
    char timestamp[20];
    char next_update[20];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Calculate next update time (30 seconds from now)
    time_t now = time(NULL);
    time_t next_time = now + UPDATE_INTERVAL;
    struct tm *next_tm = localtime(&next_time);
    if (next_tm) {
        snprintf(next_update, sizeof(next_update), "%02d:%02d:%02d",
                 next_tm->tm_hour, next_tm->tm_min, next_tm->tm_sec);
    } else {
        strcpy(next_update, "--:--:--");
    }
    
    // Clear screen for NEW table
    printf("\033[2J\033[H");
    
    // Table width is 78 characters total
    // 2 border chars + 76 content chars
    
    // Print NEW monitor header - PERFECTLY ALIGNED
    printf("╔══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         FARIS POINTS MONITOR                         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════╣\n");
    
    // Update line - FIXED PERFECT ALIGNMENT
    char update_line[100];
    snprintf(update_line, sizeof(update_line), "Update #%d | %s", update_number, timestamp);
    int update_len = strlen(update_line);
    printf("║ %s", update_line);
    // Fill remaining space (76 total - update_len - 1 space at start)
    for (int i = 0; i < 76 - update_len - 1; i++) {
        printf(" ");
    }
    printf("║\n");
    
    // Status line
    char status_line[100];
    snprintf(status_line, sizeof(status_line), "Status: %s", status);
    printf("║ %-75s ║\n", status_line);
    
    // Server line
    char server_line[100];
    snprintf(server_line, sizeof(server_line), "Server: %s:%d", SERVER_NAME, SERVER_PORT);
    printf("║ %-75s ║\n", server_line);
    
    printf("╠══════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                      ║\n");
    
    // Points line - perfectly centered
    char points_str[50];
    snprintf(points_str, sizeof(points_str), "Current Points: %d", current_points);
    int points_len = strlen(points_str);
    int left_spaces = (76 - points_len) / 2;
    printf("║");
    for (int i = 0; i < left_spaces; i++) printf(" ");
    printf("%s", points_str);
    for (int i = 0; i < 76 - left_spaces - points_len; i++) printf(" ");
    printf("║\n");
    
    printf("║                                                                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Recent Activity:                                                     ║\n");
    
    // Show last 5 activities
    int displayed = 0;
    
    if (activity_count == 0) {
        printf("║ • No recent activity                                                ║\n");
        displayed++;
    } else {
        // Show most recent activities (up to 5)
        int start = activity_count - 5;
        if (start < 0) start = 0;
        
        for (int i = start; i < activity_count && displayed < 5; i++) {
            int idx = i % MAX_ACTIVITIES;
            if (idx >= 0 && idx < MAX_ACTIVITIES && activity_log[idx].valid) {
                printf("║ %-68s ║\n", activity_log[idx].message);
                displayed++;
            }
        }
    }
    
    // Fill remaining lines with exactly the right spacing
    for (int i = displayed; i < 5; i++) {
        printf("║                                                                      ║\n");
    }
    
    printf("╠══════════════════════════════════════════════════════════════════════╣\n");
    
    // Next update line - PERFECT ALIGNMENT
    char next_line[100];
    snprintf(next_line, sizeof(next_line), "Next update at: %s", next_update);
    printf("║ %-75s ║\n", next_line);
    
    printf("╚══════════════════════════════════════════════════════════════════════╝\n");
    
    fflush(stdout);
}

int main() {
    printf("C Client (Faris) starting...\n");
    printf("Will connect to: %s:%d\n", SERVER_NAME, SERVER_PORT);
    printf("Starting with last known points: %d\n", current_points);
    printf("Update interval: %d seconds\n", UPDATE_INTERVAL);
    sleep(2);
    
    // Initialize activity log
    for (int i = 0; i < MAX_ACTIVITIES; i++) {
        activity_log[i].valid = 0;
        activity_log[i].message[0] = '\0';
    }
    
    add_activity("Starting monitor...");
    
    // Initial table
    print_new_monitor("Initializing");
    
    // Main loop - ONE table every 30 seconds
    while (1) {
        time_t cycle_start = time(NULL);
        char status[20] = "Disconnected";
        
        // Try to connect to server
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock >= 0) {
            // Set socket timeout
            struct timeval timeout;
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;
            setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
            
            struct sockaddr_in server_addr;
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(SERVER_PORT);
            
            // Resolve hostname
            struct hostent *server = gethostbyname(SERVER_NAME);
            if (server != NULL) {
                memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
                
                add_activity("Connecting to server...");
                
                if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) >= 0) {
                    strcpy(status, "Connected");
                    add_activity("Connected to server");
                    
                    // Send GET_POINTS request
                    char buffer[1024];
                    snprintf(buffer, sizeof(buffer), "GET_POINTS");
                    
                    add_activity("Sent: GET_POINTS");
                    
                    if (send(sock, buffer, strlen(buffer), 0) >= 0) {
                        // Receive response
                        memset(buffer, 0, sizeof(buffer));
                        int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
                        
                        if (bytes_received > 0) {
                            buffer[bytes_received] = '\0';
                            
                            // Parse points from response
                            int new_points = current_points;
                            
                            // Try different formats
                            char *points_str = strstr(buffer, "Faris Points:");
                            if (points_str) {
                                points_str += strlen("Faris Points:");
                                while (*points_str == ' ') points_str++;
                                new_points = atoi(points_str);
                            } 
                            else if ((points_str = strstr(buffer, "POINTS:")) != NULL) {
                                points_str += strlen("POINTS:");
                                new_points = atoi(points_str);
                            }
                            else {
                                int temp = atoi(buffer);
                                if (temp > 0) {
                                    new_points = temp;
                                }
                            }
                            
                            // Update points if valid
                            if (new_points != current_points && new_points > 0) {
                                current_points = new_points;
                            }
                            
                            // Format response for display
                            char display_response[50];
                            if (strlen(buffer) > 40) {
                                strncpy(display_response, buffer, 37);
                                display_response[37] = '\0';
                                strcat(display_response, "...");
                            } else {
                                strcpy(display_response, buffer);
                            }
                            
                            add_activity("Received: %s", display_response);
                        } else {
                            add_activity("No response from server");
                        }
                    } else {
                        add_activity("Send failed");
                        strcpy(status, "Send Error");
                    }
                } else {
                    add_activity("Connection failed");
                }
            } else {
                add_activity("Cannot resolve hostname");
                strcpy(status, "DNS Error");
            }
            
            close(sock);
        } else {
            add_activity("Socket creation error");
        }
        
        // Show ONE table for this cycle
        print_new_monitor(status);
        update_number++;
        
        // Wait exactly 30 seconds total for this cycle
        time_t cycle_end = time(NULL);
        time_t elapsed = cycle_end - cycle_start;
        
        if (elapsed < UPDATE_INTERVAL) {
            int sleep_time = UPDATE_INTERVAL - elapsed;
            sleep(sleep_time);
        }
    }
    
    return 0;
}