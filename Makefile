CC=gcc
CFLAGS=-Wall 
LDFLAGS=
executable = client server 

all: $(executable)

client: client.c structure.c structure.h
	$(CC) $(CFLAGS) client.c structure.c -o client

server: server.c structure.c structure.h
	$(CC) $(CFLAGS) server.c structure.c -o server -lpthread



.PHONY: clean 

clean:
	rm -rf *.o
	rm -rf $(executable)
	
