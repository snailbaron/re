#ifndef _TEST_H_
#define _TEST_H_

#include <stdbool.h>
#include <stdlib.h>

enum
{
    MAX_TEST_NAME_LEN = 100,
    MAX_TEST_SUITE_LEN = 100,
};

typedef bool(*test_t)();

typedef struct test_case_t test_case_t;
struct test_case_t
{
    test_t test;
    char *name;
};

test_case_t make_test_case(test_t test, const char *name);

typedef struct test_suite_t test_suite_t;
struct test_suite_t
{
    test_case_t tcs[MAX_TEST_SUITE_LEN];
    size_t size;
};

void run_test_suite(test_suite_t suite);

#define TEST_SUITE(NAME, SIZE)      \
test_suite_t NAME = {               \
    .size = SIZE,                   \
    .tcs = {

#define TEST_CASE(NAME)             \
    { NAME, #NAME },

#define TEST_SUITE_END()            \
    }                               \
};


#endif