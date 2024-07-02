// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

char buffer[LENGTH];

// Dictionary words counting
int wordCount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain its hash value
    int hashValue = hash(word);
    node *newP = table[hashValue];

    // Search the hash table at the location by the word's hash value
    while (newP != NULL)
    {
        // Compare if current word matches with node word, and return true if yes
        if (strcasecmp(word, newP->word) == 0)
        {
            return true;
        }
        newP = newP->next;
    }

    // Return false if no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    int i = 0;

    // Hash function
    while (word[i] != '\0')
    {
        sum += toupper(word[i]) - 'A';
        i++;
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize all elements of your table array to NULL with a For Loop
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Failed to open dictionary\n");
        return 1;
    }

    // Read each word in the file
    // Make sure dictionary was successfully loaded
    int result;
    while ((result = fscanf(source, "%s", buffer)) != EOF)
    {
        // Add each word to the hash table
        node *newWord = malloc(sizeof(node));
        if (newWord == NULL)
        {
            printf("Memory allocation failed\n");
            return false;
        }

        strcpy(newWord->word, buffer);
        int index = hash(buffer);

        newWord->next = table[index];
        table[index] = newWord;
        wordCount++;
    }

    // Check if you read all file and close
    if (result == EOF)
    {
        fclose(source);
        return true;
    }

    else
    {
        fclose(source);
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return that count when size is called
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // Free any memory allocated in load function
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];

        while (p != NULL)
        {
            node *tmp = p;
            p = tmp->next;
            free(tmp);
        }
    }
    return true;
}
