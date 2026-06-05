#include <string.h>
#include <ctype.h>
#include "../include/validation.h"

static void normalize_word(char *str)
{
    if (str == NULL)
    {
        return;
    }

    while (*str)
    {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

bool validate_dictionary_word(const Trie *trie, const char *word)
{
    if (trie == NULL || word == NULL || *word == '\0')
    {
        return false;
    }

    char buffer[256];

    strncpy(buffer, word, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    normalize_word(buffer);

    return trie_search(trie, buffer);
}

bool validate_letters(const char *word, const char *letters)
{
    if (word == NULL || letters == NULL || *word == '\0' || *letters == '\0')
    {
        return false;
    }

    char word_buffer[256];
    char letters_buffer[256];

    strncpy(word_buffer, word, sizeof(word_buffer) - 1);
    word_buffer[sizeof(word_buffer) - 1] = '\0';

    strncpy(letters_buffer, letters, sizeof(letters_buffer) - 1);
    letters_buffer[sizeof(letters_buffer) - 1] = '\0';

    normalize_word(word_buffer);
    normalize_word(letters_buffer);

    int frequency[ALPHABET_SIZE] = {0};

    for (int i = 0; letters_buffer[i] != '\0'; i++)
    {
        if (letters_buffer[i] < 'A' || letters_buffer[i] > 'Z')
        {
            return false;
        }

        frequency[letters_buffer[i] - 'A']++;
    }

    for (int i = 0; word_buffer[i] != '\0'; i++)
    {
        if (word_buffer[i] < 'A' || word_buffer[i] > 'Z')
        {
            return false;
        }

        int index = word_buffer[i] - 'A';
        frequency[index]--;

        if (frequency[index] < 0)
        {
            return false;
        }
    }

    return true;
}

bool validate_word(const Trie *trie, const char *word, const char *letters)
{
    if (trie == NULL || word == NULL || letters == NULL)
    {
        return false;
    }

    return validate_dictionary_word(trie, word) && validate_letters(word, letters);
}