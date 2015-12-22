#include <stdio.h>

#include <set.h>

int main()
{
    set_t *set = set_create(int);

    int val = 10;
    int val2 = 25;
    set_insert(set, &val);
    set_insert(set, &val);
    set_insert(set, &val2);
    set_insert(set, &val);
    set_insert(set, &val2);

    for (set_iter_t it = set_first(set); !set_done(&it); set_next(&it)) {
        int value;
        set_get(&it, &value);
        printf("Value: %d\n", value);        
    }

    printf("Removing\n");
    set_rm(set, &val2);

    for (set_iter_t it = set_first(set); !set_done(&it); set_next(&it)) {
        int value;
        set_get(&it, &value);
        printf("Value: %d\n", value);
    }


    set_kill(set);
}