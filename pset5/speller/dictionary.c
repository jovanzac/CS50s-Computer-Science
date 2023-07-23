// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
const unsigned int N = 26 * LENGTH;
// Number of words in the dict
int words_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int word_index = hash(word);
    // iterate through each node in the linked list and return true if the word belongs to any of those nodes.
    for (node *tmp = table[word_index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// There are LENGTH * 26, ie, 1170 buckets in the hash tables. This means that each table is ordered according to the length of the word as well as the first letter
// buckets are like: a1, a2, a3,... a45, b1, b2,... z44, z45.
unsigned int hash(const char *word)
{
    int word_len = strlen(word);
    return ((tolower(word[0]) - 97) * LENGTH) + word_len - 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *dict = fopen(dictionary, "r");

    // Allocate some memory space to store a word from the dict temporarily
    char *dict_word = malloc(LENGTH + 1);
    if (dict_word == NULL)
    {
        fclose(dict);
        unload();
        return false;
    }

    // While loop iterates for every word in the dictionary, adding each word to the hash table
    while (fscanf(dict, "%s", dict_word) != EOF)
    {
        // Allocate memmory for the node which is to store dict_word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dict);
            unload();
            return false;
        }

        // Copy dict_word to the node
        strcpy(n->word, dict_word);

        // Putting the pointer n into the beginning of the linked list in the hash table
        int word_index = hash(dict_word);
        n->next = table[word_index];
        table[word_index] = n;
        // Update words_counter
        words_counter++;
    }
    fclose(dict);
    free(dict_word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return number of words in dict
    return words_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}