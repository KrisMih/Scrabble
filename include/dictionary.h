#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stddef.h>
#include "trie.h"

#define MAX_PATH_LENGTH 256

typedef struct Dictionary
{
    Trie* trie;
    char path[MAX_PATH_LENGTH];
} Dictionary;

Dictionary* dictionary_create(const char* path);

void dictionary_destroy(Dictionary* dictionary);

bool dictionary_load(Dictionary* dictionary);

bool dictionary_add_word(Dictionary* dictionary, const char* word);

bool dictionary_contains(const Dictionary* dictionary, const char* word);

size_t dictionary_word_count(const Dictionary* dictionary);

#endif