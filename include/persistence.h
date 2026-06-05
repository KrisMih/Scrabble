#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdbool.h>
#include "trie.h"

bool trie_save(
    Trie* trie,
    const char* filename
);

Trie* trie_load(
    const char* filename
);

#endif