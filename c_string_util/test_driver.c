#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "string_util.h"

static void test_reverse_string_in_place_1(void **state) {
    /* gotcha: this _must_ be declared as an array explicitly.  
       char* (string literal) is stored in read-only memory 
       (perhaps baked-into the compiled executable). */
    char s[] = "foo";
    assert_string_equal("oof", reverse_string_in_place(s));
}
static void test_reverse_string_in_place_2(void **state) {
    char s[] = "foobarbaz";
    assert_string_equal("zabraboof", reverse_string_in_place(s));
}
static void test_reverse_string_in_place_3(void **state) {
    char s[] = "abc\0efg";
    assert_string_equal("cba", reverse_string_in_place(s));
}
static void test_reverse_string_in_place_4(void **state) {
    char s[] = "";
    assert_string_equal("", reverse_string_in_place(s));
}
static void test_reverse_string_in_place_5(void **state) {
    assert_true(NULL == reverse_string_in_place(NULL));
}

int main(int argc, char **argv) {
    const UnitTest tests[] = {
        unit_test(test_reverse_string_in_place_1),
        unit_test(test_reverse_string_in_place_2),
        unit_test(test_reverse_string_in_place_3),
        unit_test(test_reverse_string_in_place_4),
        unit_test(test_reverse_string_in_place_5),
    };

    return run_tests(tests);
}

