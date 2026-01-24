CC = gcc
CFLAGS = -Wall
LIBS = -lmysqlclient

all: server

server: server1.c
	$(CC) $(CFLAGS) -o server server1.c $(LIBS)

clean:
	rm -f server
