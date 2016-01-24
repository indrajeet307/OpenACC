CC=gcc
DEBUG=-DDEBUG = 0
GDB=-g

all: trie.c reader
	$(CC) $(GDB) trie.c -o trie.out

reader: reader.c
	$(CC) $(GDB) reader.c -o reader.out

clean: 
	rm -f *.out
