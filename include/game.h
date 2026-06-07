#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "dictionary.h"

typedef struct
{
    int score;
    GameConfig config;
    Dictionary* dictionary;
} GameState;

void game_menu(GameState* game);

void game_start(GameState* game);

void play_round(GameState* game);

void settings_menu(GameState* game);

void add_word_menu(GameState* game);

void generate_letters(GameState* game, char letters[], int count);

int calculate_score(const char* word);

#endif