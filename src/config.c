#include "../include/config.h"

GameConfig config_default(void)
{
    GameConfig config;

    config.rounds = 10;
    config.letters_per_round = 10;

    return config;
}