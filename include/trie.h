#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stddef.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
}TrieNode;

typedef struct Trie
{
    TrieNode* root;
    size_t wordCount;
}Trie;

TrieNode* trie_node_create(void);

Trie* trie_create(void);

void trie_destroy(Trie* trie);

bool trie_insert(Trie* trie, const char* word);

bool trie_search(const Trie* trie, const char* word);

bool trie_has_prefix(const Trie* trie, const char* prefix);

size_t trie_word_count(const Trie* trie);

#endif