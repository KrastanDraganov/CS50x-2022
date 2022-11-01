#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 6037;
const unsigned int BASE = 31;

node *hash_table_start[N];
node *hash_table_end[N];

int dictionary_words_counter;

bool check(const char *word)
{
    int current_hash = hash(word);

    node *table_reference = hash_table_start[current_hash];
    while (table_reference != NULL)
    {
        if (strcasecmp(word, table_reference->word) == 0)
        {
            return true;
        }

        table_reference = table_reference->next;
    }

    return false;
}

unsigned int hash(const char *word)
{
    if (word == NULL)
    {
        return 0;
    }

    unsigned int result = 0;

    while (*word != '\0')
    {
        result = ((result * BASE % N) + tolower(*word)) % N;
        ++word;
    }

    return result;
}

bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    dictionary_words_counter = 0;
    for (int i = 0; i < N; ++i)
    {
        hash_table_start[i] = NULL;
        hash_table_end[i] = NULL;
    }

    char current_char = '\0';
    int index = 0;
    char word[LENGTH + 1];

    while (fread(&current_char, sizeof(char), 1, dictionary_file))
    {
        if (current_char == '\n')
        {
            word[index++] = '\0';

            ++dictionary_words_counter;
            unsigned int current_hash = hash(word);

            node *new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = NULL;

            if (hash_table_start[current_hash] == NULL)
            {
                hash_table_start[current_hash] = new_node;
                hash_table_end[current_hash] = new_node;
            }
            else
            {
                hash_table_end[current_hash]->next = new_node;
                hash_table_end[current_hash] = hash_table_end[current_hash]->next;
            }

            memset(word, '\0', sizeof(word));
            index = 0;
        }
        else
        {
            word[index++] = current_char;
        }
    }

    fclose(dictionary_file);
    return true;
}

unsigned int size(void)
{
    return dictionary_words_counter;
}

bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node *current_node = hash_table_start[i];

        while (current_node != NULL)
        {
            node *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }

    return true;
}
