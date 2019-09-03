// Implements a dictionary's functionality

#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "dictionary.h"

//Starting of the trie and no of word read
nodes *root = NULL;
unsigned int words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create a copy of root so that we do not change root accidently
    nodes *temp;
    temp = root;
    int index = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        //To find the index for each word letter passed
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            index = word[i] - 97;
        }
        else if (word[i] == '\'')
        {
            index  =  26;
        }
        else
        {
            index = word[i] - 65;
        }
        //If child does not exist return false or set temp to child
        if (!temp->child[index])
        {
            return false;
        }
        else
        {
            temp = temp->child[index];
        }
    }
    if (temp->word == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // To create the root node and check if it was successfully created
    root = getnode();
    if (root == NULL)
    {
        return false;
    }
    char word[LENGTH];
    //To open dictionary file successfully
    FILE *in = fopen(dictionary, "r");
    if (in == NULL)
    {
        fclose(in);
        return false;
    }
    nodes *temp;
    //To read word from file till its end is reached
    while (fscanf(in, "%s", word) != EOF)
    {
        temp = root;
        int index = 0;
        for (int i = 0; i < strlen(word); i++)
        {
            //Find the index for each letter
            if (word[i] >= 'a' && word[i] <= 'z')
            {
                index = word[i] - 97;
            }
            else if (word[i]  ==  '\'')
            {
                index  =  26;
            }
            else
            {
                index = word[i] - 65;
            }
            //If the child of index is not there create one or else dive in the child node
            if (!temp->child[index])
            {
                temp->child[index] = getnode();
                temp = temp->child[index];
            }
            else
            {
                temp = temp->child[index];
            }
        }
        //Set the word member to 1 meaning true to show that the word exists
        temp->word = 1;
        words++;
    }
    //To close the file and avoid memory leaks VERY IMPROTANT...SPEND AN HOUR SEARCHING THIS ERROR
    fclose(in);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If some words were successfully read return the number of words or else return 0
    if (words > 0)
    {
        return words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Create a copy of root and pass it to delete function
    nodes *temp = root;
    bool freed = deldict(temp);
    //If the delete fucntion worked return true or else false
    if (freed == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//To delete the created nodes
bool deldict(nodes *delptr)
{
    for (int i = 0; i < 27; i++)
    {
        //If the child node exists delete it recursively
        if (delptr->child[i] != NULL)
        {
            deldict(delptr->child[i]);
        }
    }
    free(delptr);
    return true;
}

//To create a new node
nodes *getnode(void)
{
    nodes *temp  =  malloc(sizeof(nodes));
    if (temp  ==  NULL)
    {
        return NULL;
    }
    //To set values of all the children of the new node to NULL
    for (int i  =  0; i < 27; i++)
    {
        temp -> child[i]  =  NULL;
    }
    temp->word  =  0;
    return temp;
}