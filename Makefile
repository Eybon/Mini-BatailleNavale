CC=gcc
CFLAGS=-Wall
LDFLAGS=
executable = client server grille

all: $(executable)

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

grille: structure.o
	$(CC) $(CFLAGS) -o grille structure.o

structure.o: structure.c structure.h
	$(CC) $(CFLAGS) -c structure.c 	

.PHONY: clean 

clean:
	rm -rf *.o
	rm -rf $(executable)
	
