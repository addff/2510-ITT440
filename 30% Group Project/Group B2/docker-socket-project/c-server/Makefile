CC = gcc
CFLAGS = -Wall
LIBS = -lmysqlclient

all: server

server: server.c
	$(CC) $(CFLAGS) -o server server.c $(LIBS)

clean:
	rm -f server