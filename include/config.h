#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    int rounds;
    int letters_per_round;
} GameConfig;

GameConfig config_default(void);

#endif