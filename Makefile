CFLAGS = -O3 -Wall -pedantic
all: main
trie.o: trie.c trie.h
trie.o: trie.h
main.o: main.c trie.h
main: main.o trie.o
clean:
	rm -f *.o main
