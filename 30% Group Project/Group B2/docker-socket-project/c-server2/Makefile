CC = gcc
CFLAGS = -Wall
LIBS = -lmysqlclient

all: server

server: server2.c
	$(CC) $(CFLAGS) -o server server2.c $(LIBS)

clean:
	rm -f server
