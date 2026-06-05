#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include "trie.h"

bool validate_dictionary_word(const Trie* trie, const char* word);
bool validate_letters(const char* word, const char* letters);
bool validate_word(const Trie* trie, const char* word, const char* letters);

#endif