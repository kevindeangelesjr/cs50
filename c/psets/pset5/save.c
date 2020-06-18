// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Count for number of words in the dictionary
unsigned int dictCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get hash index for the current dictionary word
    unsigned int hashIndex = hash(word);

    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        return false;
    }

    cursor->next = table[hashIndex];

    while (cursor->next != NULL)
    {
        
        if (strcasecmp(cursor->word, word) == 0)
        {
            free(cursor);
            return true;
        }
        else
        {
            cursor = cursor->next;
        }   
    } 

    free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function: http://www.cse.yorku.ca/~oz/hash.html

    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open provided dictionary file
    FILE *dictFile = fopen(dictionary, "r");

    // Return false if the dictionary file could not be opened
    if (dictFile == NULL)
    {
        printf("File could not be opened.\n");
        return false;
    }

    char *word = malloc(LENGTH);

    // Read each line of the dictionary file
    while (fscanf(dictFile, "%s", word) != EOF)
    {
        // Increment dictCount - number of words in dictionary
        dictCount++;

        // Create new linked list node, return false if it memory was not allocated
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy current word from the dictionary into the new node that was created
        strcpy(n->word, word);

        // Get has index for the current dictionary word
        unsigned int hashIndex = hash(word);

        if (table[hashIndex] == NULL)
        {
            table[hashIndex] = n;
        }
        else
        {
            n->next = table[hashIndex]->next;
            table[hashIndex]->next = n;
        }
    } 

    fclose(dictFile);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = malloc(sizeof(node));
    node *tmp = malloc(sizeof(node));

    // Free list
    for (int i = 0; i < N; i ++)
    {
        cursor-> next = table[i];

        while (cursor->next != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;   
            free(tmp);
        }
    } 

    free(cursor);
    free(tmp);
    return true;
}