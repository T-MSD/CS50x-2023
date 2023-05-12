// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 457653;

// Hash table
node *table[N];

// First element of the linked list (only used in unload)
node *head_remove = NULL;

// Counter for the words in the dictionary
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int pos = hash(word);
    node *node = table[pos];
    while (node != NULL)
    {
        // Case insensitive
        if (strcasecmp(node->word, word) == 0)
        {
            return true;
        }
        node = node->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 0;
    int length = strlen(word);
    for (int i = 0; i < length && i < 4; i++)
    {
        value += toupper(word[i]) - atoi("A");
    }
    return value + 1;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    char new_word[LENGTH + 1];
    int pos;
    if (inptr == NULL)
    {
        return false;
    }
    // Read from the file
    while (fscanf(inptr, "%s", new_word) == 1)
    {
        pos = hash(new_word);
        // First element of the linked list
        if (table[pos] == NULL)
        {
            node *head = (node *)malloc(sizeof(node));
            strcpy(head->word, new_word);
            head->next = NULL;
            table[pos] = head;
        }
        // All the other elements
        else
        {
            node *aux;
            node *new_node = (node *)malloc(sizeof(node));
            strcpy(new_node->word, new_word);
            aux = table[pos];
            table[pos] = new_node;
            new_node->next = aux;
        }
        word_counter++;
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *aux;
        head_remove = table[i];
        while (head_remove != NULL)
        {
            aux = head_remove;
            head_remove = head_remove->next;
            free(aux);
        }
    }
    return true;
}