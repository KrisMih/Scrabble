#include <stdlib.h>
#include <ctype.h>
#include "../include/trie.h"

TrieNode* trie_node_create(void)
{
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));

    if(node == NULL)
    {
        return NULL;
    }

    node->isEndOfWord = false;

    return node;
}

static void trie_node_destroy(TrieNode* node)
{

    if(node == NULL)
    {
        return;
    }

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        trie_node_destroy(node->children[i]);
    }

    free(node);
}

static int get_index(char c)
{
    c = (char)toupper((unsigned char)c);

    if(c < 'A' || c > 'Z')
    {
        return -1;
    }

    return c - 'A';
}

Trie* trie_create(void)
{
    Trie* trie = (Trie*)malloc(sizeof(Trie));

    if(trie == NULL)
    {
        return NULL;
    }

    trie->root = trie_node_create();

    if(trie->root == NULL)
    {
        free(trie);
        return NULL;
    }

    trie->wordCount = 0;

    return trie;
}

void trie_destroy(Trie* trie)
{

    if(trie == NULL)
    {
        return;
    }

    trie_node_destroy(trie->root);

    free(trie);
}

bool trie_insert(Trie* trie, const char* word)
{
    
    if(trie == NULL || word == NULL)
    {
        return false;
    }

    TrieNode* current = trie->root;

    while(*word)
    {
        int index = get_index(*word);

        if(index == -1)
        {
            return false;
        }

        if(current->children[index] == NULL)
        {
            current->children[index] = trie_node_create();

            if(current->children[index] == NULL)
            {
                return false;
            }

        }

        current = current->children[index];

        word++;
    }

    if(current->isEndOfWord)
    {
        return false;
    }

    current->isEndOfWord = true;

    trie->wordCount++;

    return true;
}

bool trie_search(const Trie* trie, const char* word)
{

    if(trie == NULL || word == NULL)
    {
        return false;
    }

    const TrieNode* current = trie->root;

    while(*word)
    {
        int index = get_index(*word);

        if(index == -1)
        {
            return false;
        }

        if(current->children[index] == NULL)
        {
            return false;
        }

        current = current->children[index];

        word++;
    }

    return current->isEndOfWord;
}

bool trie_has_prefix(const Trie* trie, const char* prefix)
{

    if(trie == NULL || prefix == NULL)
    {
        return false;
    }

    const TrieNode* current = trie->root;

    while(*prefix)
    {
        int index = get_index(*prefix);

        if(index == -1)
        {
            return false;
        }

        if(current->children[index] == NULL)
        {
            return false;
        }

        current = current->children[index];

        prefix++;
    }

    return true;
}

size_t trie_word_count(const Trie* trie)
{

    if(trie == NULL)
    {
        return 0;
    }

    return trie->wordCount;
}