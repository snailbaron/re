#include "../re/src/set.h"
#include <stdbool.h>

bool test_set_mult_creation()
{
    set_t *set = NULL;
    set = set_create(sizeof(int));
    set_kill(set);
    set = set_create(sizeof(int));
    set_kill(set);
    return true;
}

bool test_set_add_rm()
{
    bool ok = true;

    set_t *set = NULL;
    set = set_create(sizeof(int));
    if (set_size(set) != 0) {
        ok = false;
    }

    int i1 = 1, i2 = 2, i3 = 3;
    set_add(set, &i1);
    set_add(set, &i2);
    set_add(set, &i3);
    if (set_size(set) != 3) {
        ok = false;
    }

    set_kill(set);
    return ok;
}