#include <stdio.h>
#include "../include/dictionary.h"
#include "../include/validation.h"

static void print_result(const char* test_name, int result, int expected)
{
    printf("%s -> %d (expected %d)%s\n",
           test_name,
           result,
           expected,
           result == expected ? " [OK]" : " [FAIL]");
}

int main(void)
{
    Dictionary* dict = dictionary_create("data/dictionary.txt");

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

    Trie* trie = dict->trie;

    printf("=====================================\n");
    printf("VALIDATION TESTS\n");
    printf("=====================================\n\n");

    printf("=== validate_dictionary_word ===\n");
    print_result("CAT", validate_dictionary_word(trie, "CAT"), 1);
    print_result("cat", validate_dictionary_word(trie, "cat"), 1);
    print_result("DoG", validate_dictionary_word(trie, "DoG"), 1);
    print_result("HOUSE", validate_dictionary_word(trie, "HOUSE"), 1);
    print_result("NOTEXIST", validate_dictionary_word(trie, "NOTEXIST"), 0);
    print_result("CAT123", validate_dictionary_word(trie, "CAT123"), 0);
    print_result("", validate_dictionary_word(trie, ""), 0);

    printf("\n=== validate_letters ===\n");
    print_result("APPLE from AAPPLE", validate_letters("APPLE", "AAPPLE"), 1);
    print_result("APPLE from AATPLE", validate_letters("APPLE", "AATPLE"), 0);
    print_result("CAT from ABCATT", validate_letters("CAT", "ABCATT"), 1);
    print_result("CAT from ABCT", validate_letters("CAT", "ABCT"), 1);
    print_result("DOG from DOGO", validate_letters("DOG", "DOGO"), 1);
    print_result("DOG from DO", validate_letters("DOG", "DO"), 0);
    print_result("CAT123 from ABCATT", validate_letters("CAT123", "ABCATT"), 0);
    print_result("empty word", validate_letters("", "ABCATT"), 0);

    printf("\n=== validate_word ===\n");
    print_result("CAT from ABCATT", validate_word(trie, "CAT", "ABCATT"), 1);
    print_result("DOG from ABCATT", validate_word(trie, "DOG", "ABCATT"), 0);
    print_result("CAT from XYZ", validate_word(trie, "CAT", "XYZ"), 0);
    print_result("NOTEXIST from XYZ", validate_word(trie, "NOTEXIST", "XYZ"), 0);
    print_result("cat from ABCATT", validate_word(trie, "cat", "ABCATT"), 1);
    print_result("CAT123 from ABCATT", validate_word(trie, "CAT123", "ABCATT"), 0);

    printf("\n=====================================\n");
    printf("TESTS FINISHED\n");
    printf("=====================================\n");

    dictionary_destroy(dict);
    return 0;
}