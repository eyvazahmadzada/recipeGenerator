CC=gcc  #compiler

all:
	$(CC) reader.c -o reader
	$(CC) writer.c -o writer

clean:
	rm reader writer
