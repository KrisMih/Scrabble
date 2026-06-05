#include <stdio.h>

#include "../include/dictionary.h"

int main(void)
{
    Dictionary* dict =
        dictionary_create("data/dictionary.txt");

    if(dict == NULL)
    {
        printf("Dictionary create failed!\n");
        return 1;
    }

    if(!dictionary_load(dict))
    {
        printf("Dictionary load failed!\n");

        dictionary_destroy(dict);

        return 1;
    }

    printf("=====================================\n");
    printf("INITIAL DICTIONARY TEST\n");
    printf("=====================================\n");

    printf("Words loaded: %zu\n",
           dictionary_word_count(dict));

    printf("CAT: %d\n",
           dictionary_contains(dict, "CAT"));

    printf("DOG: %d\n",
           dictionary_contains(dict, "DOG"));

    printf("HOUSE: %d\n",
           dictionary_contains(dict, "HOUSE"));

    printf("NOTEXIST: %d\n",
           dictionary_contains(dict, "NOTEXIST"));

    printf("\n");

    printf("=====================================\n");
    printf("CASE INSENSITIVE TEST\n");
    printf("=====================================\n");

    printf("cat: %d\n",
           dictionary_contains(dict, "cat"));

    printf("DoG: %d\n",
           dictionary_contains(dict, "DoG"));

    printf("aPpLe: %d\n",
           dictionary_contains(dict, "aPpLe"));

    printf("\n");

    printf("=====================================\n");
    printf("ADD WORD TEST\n");
    printf("=====================================\n");

    if(dictionary_add_word(dict, "NEWWORD"))
    {
        printf("NEWWORD added successfully\n");
    }
    else
    {
        printf("Failed to add NEWWORD\n");
    }

    printf("NEWWORD exists: %d\n",
           dictionary_contains(dict, "NEWWORD"));

    printf("Word count: %zu\n",
           dictionary_word_count(dict));

    printf("\n");

    printf("=====================================\n");
    printf("DUPLICATE TEST\n");
    printf("=====================================\n");

    if(dictionary_add_word(dict, "CAT"))
    {
        printf("CAT added again\n");
    }
    else
    {
        printf("Duplicate CAT detected\n");
    }

    printf("Word count: %zu\n",
           dictionary_word_count(dict));

    printf("\n");

    printf("=====================================\n");
    printf("INVALID WORD TEST\n");
    printf("=====================================\n");

    printf("CAT123 -> %d\n",
           dictionary_add_word(dict, "CAT123"));

    printf("HELLO! -> %d\n",
           dictionary_add_word(dict, "HELLO!"));

    printf("123 -> %d\n",
           dictionary_add_word(dict, "123"));

    printf("\n");

    printf("=====================================\n");
    printf("FINAL WORD COUNT\n");
    printf("=====================================\n");

    printf("Words loaded: %zu\n",
           dictionary_word_count(dict));

    dictionary_destroy(dict);

    return 0;
}