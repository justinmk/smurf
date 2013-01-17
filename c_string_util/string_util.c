#include <stdio.h>
#include <stdlib.h>
#include "string_util.h"

char* reverse_string(char* s) {
    int i = 0;
    int j = 0;
    int end_char_index = -1;
    char tmp_char;

    printf("ok1\n");
    for (i = 0; s[i+1] != 0; i++) {
        printf("ok2\n");
        end_char_index = i;
        if (i > 10000) {
            printf("very long string detected\n");
        }
    }
    printf("ok3 i:%d \n", i);

    /*
     * "abc" => "cba"
     * "abcd" => "dcba"
     */
    for (i = 0, j = end_char_index; i != j && i < j; i++, j--) {
        printf("i:%s, j:%s\n", &s[i], &s[j]);
        tmp_char = s[i];
        s[i] = s[j];
        s[j] = tmp_char;
    }

    return s;
}


