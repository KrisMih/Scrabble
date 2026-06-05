#include "persistence.h"
#include "../include/trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static bool serialize_node(
    FILE* file,
    TrieNode* node
);

static TrieNode* deserialize_node(
    FILE* file
);

bool trie_save(Trie* trie, const char* filename)
{
    if (!trie || !filename)
    {
        return false;
    }

    FILE* file = fopen(filename, "wb");

    if (!file)
    {
        return false;
    }

    fwrite("TRIE", sizeof(char), 4, file);

    serialize_node(file, trie->root);

    fclose(file);

    return true;
}

Trie* trie_load(const char* filename)
{
    FILE* file = fopen(filename, "rb");

    if (!file)
    {
        return NULL;
    }

    char magic[5] = {0};

    fread(magic, sizeof(char), 4, file);

    if (strcmp(magic, "TRIE") != 0)
    {
        fclose(file);
        return NULL;
    }

    Trie* trie = trie_create();

    if (!trie)
    {
        fclose(file);
        return NULL;
    }

    trie->root = deserialize_node(file);

    fclose(file);

    return trie;
}

static bool serialize_node(FILE* file, TrieNode* node)
{
    if (!node)
    {
        uint8_t nullFlag = 0;
        fwrite(&nullFlag, sizeof(uint8_t), 1, file);
        return true;
    }

    uint8_t exists = 1;
    fwrite(&exists, sizeof(uint8_t), 1, file);
    fwrite(&node->isEndOfWord, sizeof(int), 1, file);

    for (int i = 0; i < 26; i++)
    {
        serialize_node(file, node->children[i]);
    }

    return true;
}

static TrieNode* deserialize_node(FILE* file)
{
    uint8_t exists;
    fread(&exists, sizeof(uint8_t), 1, file);

    if (!exists)
    {
        return NULL;
    }

    TrieNode* node = trie_node_create();

    fread(&node->isEndOfWord, sizeof(int), 1, file);

    for (int i = 0; i < 26; i++)
    {
        node->children[i] = deserialize_node(file);
    }

    return node;
}