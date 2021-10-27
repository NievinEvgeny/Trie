#pragma once

#define ALPHABET 30

struct Trie
{
    int value;
    int isLeaf; // "1" если узел - лист
    struct Trie* character[ALPHABET];
};

struct Trie* trieCreate();

int isLeaf(struct Trie* node);

void Print(struct Trie* root, char str[], int level);

void triePrint(struct Trie* root, char str[]);

int trieLookup(struct Trie* head, char* str);

void trieInsert(struct Trie** root, char* str, int value);

int hasChildren(struct Trie* curr);

int trieDelete(struct Trie** curr, char* str);