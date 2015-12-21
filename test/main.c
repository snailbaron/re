#include <set.h>
#include <stdio.h>

#include <list.h>

int main()
{
    list_t *list = list_create(int);

    list_iter_t *it = list_start_iter(list);
    for (int i = 0; i < 10; i++) {
        list_add(it, &i);
        list_next(it);
    }
    list_end_iter(it);


    for (list_iter_t *it = list_start_iter(list); !list_end(it); list_next(it)) {
        int value;
        list_get(it, &value);
        printf("Value: %d\n", value);
    }
    list_end_iter(it);
    
        

        

    
}