all: trie.c main.c
		gcc -Wall -o trie $^
clean:
		rm trie