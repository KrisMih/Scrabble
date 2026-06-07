#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../include/game.h"
#include "../include/validation.h"

static void to_uppercase(char* str)
{
    while(*str)
    {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

/* ---------- NEW: pick random word from dictionary file ---------- */
static void get_random_word_from_dictionary(Dictionary* dict, char* out_word)
{
    FILE* file = fopen(dict->path, "r");

    if(!file)
    {
        strcpy(out_word, "APPLE");
        return;
    }

    char word[256];
    int count = 0;

    while(fgets(word, sizeof(word), file))
    {
        count++;
    }

    if(count == 0)
    {
        strcpy(out_word, "APPLE");
        fclose(file);
        return;
    }

    rewind(file);

    int target = rand() % count;

    for(int i = 0; i <= target; i++)
    {
        fgets(word, sizeof(word), file);
    }

    word[strcspn(word, "\r\n")] = 0;

    strcpy(out_word, word);

    fclose(file);
}

/* ---------- NEW GENERATOR (dictionary-based) ---------- */
void generate_letters(GameState* game, char letters[], int count)
{
    char base_word[256];

    get_random_word_from_dictionary(game->dictionary, base_word);

    int len = strlen(base_word);
    int index = 0;

    for(int i = 0; i < len && index < count; i++)
    {
        letters[index++] = base_word[i];
    }

    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while(index < count)
    {
        letters[index++] = alphabet[rand() % 26];
    }

    for(int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char tmp = letters[i];
        letters[i] = letters[j];
        letters[j] = tmp;
    }

    letters[count] = '\0';
}

/* ---------- SCORE ---------- */
int calculate_score(const char* word)
{
    return (int)strlen(word);
}

/* ---------- ROUND ---------- */
void play_round(GameState* game)
{
    char letters[256];
    char word[256];

    generate_letters(
        game,
        letters,
        game->config.letters_per_round
    );

    printf("\nAvailable letters:\n%s\n", letters);

    while(1)
    {
        printf("Enter word: ");
        scanf("%255s", word);

        to_uppercase(word);

        if(validate_word(
            game->dictionary->trie,
            word,
            letters))
        {
            break;
        }

        printf("Invalid word. Try again.\n");
    }

    int points = calculate_score(word);

    game->score += points;

    printf("Points: %d\n", points);
    printf("Total score: %d\n", game->score);
}

/* ---------- GAME START ---------- */
void game_start(GameState* game)
{
    game->score = 0;

    for(int i = 1; i <= game->config.rounds; i++)
    {
        printf("\n===== ROUND %d =====\n", i);
        play_round(game);
    }

    printf("\nFinal score: %d\n", game->score);
}

/* ---------- SETTINGS ---------- */
void settings_menu(GameState* game)
{
    int choice;

    do
    {
        printf("\nSettings\n");
        printf("1. Change letters count\n");
        printf("2. Change rounds count\n");
        printf("3. Back\n");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("New letters count: ");
                scanf("%d", &game->config.letters_per_round);
                break;

            case 2:
                printf("New rounds count: ");
                scanf("%d", &game->config.rounds);
                break;

            case 3:
                break;

            default:
                printf("Invalid option.\n");
        }

    } while(choice != 3);
}

/* ---------- ADD WORD ---------- */
void add_word_menu(GameState* game)
{
    char word[256];

    printf("Word: ");
    scanf("%255s", word);

    if(dictionary_add_word(game->dictionary, word))
    {
        printf("Word added.\n");
    }
    else
    {
        printf("Failed to add word.\n");
    }
}

/* ---------- MENU ---------- */
void game_menu(GameState* game)
{
    int choice;

    do
    {
        printf("\n");
        printf("1. Start New Game\n");
        printf("2. Settings\n");
        printf("3. Add New Word\n");
        printf("4. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                game_start(game);
                break;

            case 2:
                settings_menu(game);
                break;

            case 3:
                add_word_menu(game);
                break;

            case 4:
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);
}