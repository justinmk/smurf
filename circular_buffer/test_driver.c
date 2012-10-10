#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cbuff.h"
#include <cmockery.h>

// http://code.google.com/p/mongoose/
// http://stackoverflow.com/questions/7315936/which-of-fprintf-snprintf-is-more-secure
// vsnprintf: http://stackoverflow.com/a/4627539/152142
// http://news.ycombinator.com/item?id=3970870

int tests_run = 0;
int cbuff_size = 0;
cbuff_t* cbuff;

extern const char* get_status_code_string(const unsigned int status_code);
extern unsigned int string_to_status_code(
    const char* const status_code_string);

void test_cbuff_lifecycle(void **state) {
    cbuff_inspect(cbuff);

    /* oldest element should be CBUFF_EMPTY */
    assert_true(CBUFF_EMPTY == cbuff_remove(cbuff));

    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 1);
    cbuff_inspect(cbuff);

    /* oldest element should be 1 */
    assert_int_equal(1, cbuff_remove(cbuff));

    cbuff_inspect(cbuff);

    cbuff_remove(cbuff);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 1);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 2);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 3);
    cbuff_inspect(cbuff);

    assert_int_equal(1, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    assert_int_equal(2, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 4);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 5);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 6);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 7);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 8);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 9);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 0);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 1);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 2);
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 3);
    cbuff_inspect(cbuff);

    assert_int_equal(5, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    cbuff_remove(cbuff);
    cbuff_inspect(cbuff);

    cbuff_remove(cbuff);
    cbuff_inspect(cbuff);

    cbuff_remove(cbuff);
    cbuff_inspect(cbuff);

    cbuff_remove(cbuff);
    cbuff_inspect(cbuff);

    assert_int_equal(0, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    assert_int_equal(1, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    assert_int_equal(2, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 1);
    cbuff_inspect(cbuff);

    assert_int_equal(3, cbuff_remove(cbuff));
    cbuff_inspect(cbuff);

    cbuff_add(cbuff, 1);
    cbuff_inspect(cbuff);
}

int main(int argc, char **argv) {
    const UnitTest tests[] = {
        unit_test(test_cbuff_lifecycle),
    };
    cbuff_size = atoi(argv[1]);
    cbuff = cbuff_init(cbuff_size);

    return run_tests(tests);
}

// http://linux.die.net/man/3/snprintf

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//
//char *
//make_message(const char *fmt, ...)
//{
//    int n;
//    int size = 100;     /* Guess we need no more than 100 bytes. */
//    char *p, *np;
//    va_list ap;
//
//   if ((p = malloc(size)) == NULL)
//        return NULL;
//
//   while (1) {
//
//       /* Try to print in the allocated space. */
//
//       va_start(ap, fmt);
//        n = vsnprintf(p, size, fmt, ap);
//        va_end(ap);
//
//       /* If that worked, return the string. */
//
//       if (n > -1 && n < size)
//            return p;
//
//       /* Else try again with more space. */
//
//       if (n > -1)    /* glibc 2.1 */
//            size = n+1; /* precisely what is needed */
//        else           /* glibc 2.0 */
//            size *= 2;  /* twice the old size */
//
//       if ((np = realloc (p, size)) == NULL) {
//            free(p);
//            return NULL;
//        } else {
//            p = np;
//        }
//    }
//}
