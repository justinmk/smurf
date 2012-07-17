#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

// http://code.google.com/p/mongoose/
// http://stackoverflow.com/questions/7315936/which-of-sprintf-snprintf-is-more-secure
// http://stackoverflow.com/a/4627539/152142
// http://news.ycombinator.com/item?id=3970870


int main(int argc, char **argv) {
    int cbuff_size = 0;
    cbuff_t cbuff;

    cbuff_size = atoi(argv[1]);

    cbuff_init(&cbuff, cbuff_size);
    cbuff_inspect(&cbuff);

    if (CBUFF_EMPTY != cbuff_remove(&cbuff)) {
        printf("ERROR");
    }
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 1);
    cbuff_inspect(&cbuff);

    if (1 != cbuff_remove(&cbuff)) {
        printf("ERROR");
    }
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 1);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 2);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 3);
    cbuff_inspect(&cbuff);

    if (1 != cbuff_remove(&cbuff)) {
        printf("ERROR");
    }
    cbuff_inspect(&cbuff);

    if (2 != cbuff_remove(&cbuff)) {
        printf("ERROR");
    }
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 4);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 5);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 6);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 7);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 8);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 9);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 0);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 1);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 2);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 3);
    cbuff_inspect(&cbuff);

    if (5 != cbuff_remove(&cbuff)) {
        printf("ERROR: oldest element should be 5");
    }
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 1);
    cbuff_inspect(&cbuff);

    cbuff_remove(&cbuff);
    cbuff_inspect(&cbuff);

    cbuff_add(&cbuff, 1);
    cbuff_inspect(&cbuff);

    return 0;
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
