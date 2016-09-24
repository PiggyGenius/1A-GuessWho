#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdbool.h>

#define CHECK(msg,cond) __check(msg, cond, __FILE__, __LINE__);

static inline void __check(const char *msg, bool cond, const char *file, unsigned line)
{
    if (cond) {
        printf("\033[32;1m[PASS]\033[0m %-40s\t(%s:%i)\n", msg, file, line);
    } else {
        printf("\033[31;1m[FAIL]\033[0m %-40s\t(%s:%i)\n", msg, file, line);
    }
}

#endif /* TESTS_H */
