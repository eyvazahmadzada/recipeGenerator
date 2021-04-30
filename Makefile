CC=gcc  #compiler

all:
	$(CC) src/reader/reader.c src/reader/main.c -o build/reader
	$(CC) src/writer/writer.c src/writer/main.c -o build/writer

clean:
	rm build/*