// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
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

    // Create a temporary node called cursor to iterate over linked list at this index
    node *cursor = table[hashIndex];
    if (cursor == NULL)
    {
        return false;
    }

    // Move through linked list until you hit the end
    while (cursor != NULL)
    {
        // Compare the word value of the current node in the linked list to word passed to the function
        // If it matches, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        // Move to temporary node to the next node in the linked list
        cursor = cursor->next; 
    } 
    
    // We've hit the end of the linked list at this index of the hash table and haven't found the word.  Return false
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

    // Buffer for each word of the dictionary
    char *word = malloc(LENGTH + 1);

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

        // Add the new node to the beginning of the linked list at the current index of the hash table
        n->next = table[hashIndex];
        table[hashIndex] = n;
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
    // Iterate through each index of the hashtable
    for (int i = 0; i < N; i ++)
    {
        // Create temporary node cursor
        node *cursor = table[i];

        // Move through linked list at this index until the end
        while (cursor != NULL)
        {
            // Create second temporary node tmp, set to same value as cursor
            // This will be used for clearing, cursor will point to the next node so as to not lose place
            node *tmp = cursor;

            // Move cursor to the next node in the linked list
            cursor = cursor->next;   

            // Free the node at tmp
            free(tmp);
        }
        free(cursor);
    }

    return true;
}