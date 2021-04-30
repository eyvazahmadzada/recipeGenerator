CC=gcc  #compiler

all:
	$(CC) server.c -o server
	$(CC) client.c -o client

clean:
	rm server client
