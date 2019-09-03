// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//strucutre to store dictionary ia a trie
typedef struct node
{
    int word;
    struct node *child[27];
} nodes;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
nodes *getnode(void);
bool deldict(nodes *delptr);

#endif // DICTIONARY_H
