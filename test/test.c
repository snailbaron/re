#include "test.h"
#include <string.h>
#include <stdio.h>

test_case_t make_test_case(test_t test, const char *name)
{
    test_case_t tc = { .test = test, .name = NULL };
    strncpy_s(tc.name, MAX_TEST_NAME_LEN + 1, name, MAX_TEST_NAME_LEN);
    return tc;
}

void run_test_suite(test_suite_t suite)
{
    for (size_t i = 0; i < suite.size; i++) {
        bool result = suite.tcs[i].test();
        printf("%s : ", suite.tcs[i].name);
        if (result) {
            printf("OK\n");
        }
        else {
            printf("ERROR\n");
        }
    }
}