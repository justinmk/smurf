#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "string_util.h"
#include <cmockery.h>

extern const char* get_status_code_string(const unsigned int status_code);
extern unsigned int string_to_status_code(const char* const status_code_string);

void test_cbuff_lifecycle(void **state) {
    /* oldest element should be CBUFF_EMPTY */
    assert_string_equal("foo", reverse_string("oof"));
}

int main(int argc, char **argv) {
    char s[] = "foobarbaz\n";
    const UnitTest tests[] = {
        unit_test(test_cbuff_lifecycle),
    };

    printf("%s", s);
    reverse_string(s);
    printf("%s", s);

    return run_tests(tests);
}

