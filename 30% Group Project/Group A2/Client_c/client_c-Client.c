#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
    printf("[C CLIENT] running\n");
    while (1) {
        sleep(10);
    }
    return 0;
}
