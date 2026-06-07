#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/game.h"
#include "../include/config.h"
#include "../include/dictionary.h"
#include "../include/persistence.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    Dictionary* dictionary =
        dictionary_create(
            "data/dictionary.txt"
        );

    if(dictionary == NULL)
    {
        printf("Failed to create dictionary.\n");
        return 1;
    }

    if(!dictionary_load(dictionary))
    {
        printf("Failed to load dictionary.\n");

        dictionary_destroy(dictionary);

        return 1;
    }

    GameState game;

    game.score = 0;
    game.config = config_default();
    game.dictionary = dictionary;

    game_menu(&game);

    trie_save(
        dictionary->trie,
        "data/trie.bin"
    );

    dictionary_destroy(dictionary);

    return 0;
}