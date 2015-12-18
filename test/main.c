#include "test.h"
#include "test_set.h"

int main()
{
    TEST_SUITE(suite, 2)
        TEST_CASE(test_set_mult_creation)
        TEST_CASE(test_set_add_rm)
    TEST_SUITE_END()


    run_test_suite(suite);
}