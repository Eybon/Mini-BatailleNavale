CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
executable = client server

all: $(executable)

client: client.c
	$(CC) client.c -o client

server: server.c
	$(CC) server.c -o server

.PHONY: clean 

clean:
	rm -rf *.o
	rm -rf $(executable)
	
