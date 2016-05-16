/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dictionary.h"

//set the size of the hash table (number of buckets)
#define NUM_BUCKETS 65532

//typedefines struct called node consisting of a char array and a pointer
//called next
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// declare word counter, initialized to 0 (global vars init to 0 by default)
int wordcount;

//declare the hash table as an array of nodes, initialize to NULL
node* hashtable[NUM_BUCKETS] = {NULL};

//declare hashing function, which assigns bucket values to words from dict.
// hashing function was found online (DJB2)
unsigned int hashfun(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c;

    return hash % NUM_BUCKETS;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // since word is a pointer to a const char, which cannot be changed, we need
    //to make a copy of word in order to convert to lowercase
    char* word_lower = malloc(strlen(word));
    
    // convert string to lowercase
    for (int i = 0; i < strlen(word); i++)
    {
        word_lower[i] = tolower(word[i]);
    }
    
    // add null terminator
    word_lower[strlen(word)] = '\0';
    
    // create a cursor initialized to point to the first node
    node* cursor = hashtable[hashfun(word_lower)];
    while (cursor != NULL)
    {
        if(strcmp(word_lower, cursor->word) == 0)
        {
            free(word_lower);
            return true;
        }
        cursor = cursor->next;
    }
    free(word_lower);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Create file pointer to dictionary, check for error
    FILE* fp = fopen(dictionary, "r");
    if(fp == NULL)
    {
        printf("Could not load dictionary");
        return false;
    }
    
    // initialize a buffer the max length of a word +1 for \n...plus another 1
    //but i don't really know why. used trial and error after testing.
    char buffer[LENGTH + 2];
    
    // scan whole dictionary, loop while a NULL character is not reached
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            // change line breaks to null terminator
            buffer[strlen(buffer) - 1] = '\0';
            
            // create a new node and initialize "next" pointer to NULL
            node* new_node = malloc(sizeof(node));
            new_node->next = NULL;
            
            // copy LENGTH+1 elements of buffer into word field of new node
            strncpy(new_node->word, buffer, LENGTH + 1);

            // run the word through the hash function to get bucket number
            int bucket = hashfun(new_node->word);
            
            // if there is no linked list at the bucket, insert anchor there
            if (hashtable[bucket] == NULL)
                {
                    // point head at new node
                    hashtable[bucket] = new_node;
                }
            
            // otherwise, insert in linked list
            else
            {   
                // point new node's "next" field at same node the head of the
                //linked list is pointing at (NOTE: hashtable is an array of
                //pointers to nodes, not an array of nodes)
                new_node->next = hashtable[bucket];
                // now point the head at the new node
                hashtable[bucket] = new_node;
            }
            
            //increment the word counter
            wordcount++;
        }
    fclose(fp);
        
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
