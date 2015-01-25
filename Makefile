CC=gcc
CFLAGS=-Wall 
LDFLAGS=
executable = client server 

all: $(executable)

client: client.c structure.o structure.h
	$(CC) $(CFLAGS) client.c structure.o -o client

server: server.c structure.o structure.h
	$(CC) $(CFLAGS) server.c structure.o -o server -lpthread

structure: structure.c structure.h
	$(CC) $(CFLAGS) -c structure.c

.PHONY: clean 

clean:
	rm -rf *.o
	rm -rf $(executable)
	
