#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/dictionary.h"

static void remove_newline(char* str)
{

    if(str == NULL)
    {
        return;
    }

    str[strcspn(str, "\r\n")] = '\0';
}

static void normalize_word(char* str)
{

    if(str == NULL)
    {
        return;
    }

    while(*str)
    {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }

}

static bool is_valid_word(const char* word)
{

    if(word == NULL || *word == '\0')
    {
        return false;
    }

    while(*word)
    {

        if(*word < 'A' || *word > 'Z')
        {
            return false;
        }

        word++;
    }

    return true;
}

Dictionary* dictionary_create(const char* path)
{
    if(path == NULL)
    {
        return NULL;
    }

    Dictionary* dictionary =
        (Dictionary*)malloc(sizeof(Dictionary));

    if(dictionary == NULL)
    {
        return NULL;
    }

    dictionary->trie = trie_create();

    if(dictionary->trie == NULL)
    {
        free(dictionary);
        return NULL;
    }

    strncpy(dictionary->path, path, MAX_PATH_LENGTH - 1);

    dictionary->path[MAX_PATH_LENGTH - 1] = '\0';

    return dictionary;
}

void dictionary_destroy(Dictionary* dictionary)
{

    if(dictionary == NULL)
    {
        return;
    }

    trie_destroy(dictionary->trie);

    free(dictionary);
}

bool dictionary_load(Dictionary* dictionary)
{

    if(dictionary == NULL)
    {
        return false;
    }

    FILE* file = fopen(dictionary->path, "r");

    if(file == NULL)
    {
        return false;
    }

    char buffer[256];

    while(fgets(buffer, sizeof(buffer), file))
    {
        remove_newline(buffer);

        normalize_word(buffer);

        if(!is_valid_word(buffer))
        {
            continue;
        }

        trie_insert(dictionary->trie, buffer);
    }

    fclose(file);

    return true;
}

bool dictionary_add_word(Dictionary* dictionary, const char* word)
{

    if(dictionary == NULL || word == NULL)
    {
        return false;
    }

    char buffer[256];

    strncpy(buffer, word, sizeof(buffer) - 1);

    buffer[sizeof(buffer) - 1] = '\0';

    normalize_word(buffer);

    if(!is_valid_word(buffer))
    {
        return false;
    }

    return trie_insert(dictionary->trie, buffer);
}

bool dictionary_contains(const Dictionary* dictionary, const char* word)
{

    if(dictionary == NULL || word == NULL)
    {
        return false;
    }

    char buffer[256];

    strncpy(buffer, word, sizeof(buffer) - 1);

    buffer[sizeof(buffer) - 1] = '\0';

    normalize_word(buffer);

    return trie_search(dictionary->trie, buffer);
}

size_t dictionary_word_count(const Dictionary* dictionary)
{

    if(dictionary == NULL)
    {
        return 0;
    }

    return trie_word_count(dictionary->trie);
}