#include <stdio.h>
#include <stdlib.h>
#include "string_util.h"

char* reverse_string_in_place(char* s) {
    int i = 0;
    int j = 0;/* char immediately before null char '\0' */
    char tmp_char;
    if (NULL == s) {
        return NULL;
    }

    for (j = 0; s[j] != 0; j++) {
        if (j > 10000) {
            printf("warning: very long string detected\n");
        }
    }
    j--;

    /*
     * "abc" => "cba"
     * "abcd" => "dcba"
     */
    for (i = 0; i != j && i < j; i++, j--) {
        tmp_char = s[i];
        s[i] = s[j];
        s[j] = tmp_char;
    }

    return s;
}


