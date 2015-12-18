#include <set.h>
#include <stdio.h>

struct data
{
    int number;
    char str[10];
};

void print_data(struct data *d)
{
    printf("Data: %d | %s\n", d->number, d->str);
}

int main()
{
    struct data d1 = { 10, "hi" };
    struct data d2 = { -5, "Hello" };


    set_t *set = set_create(struct data);

    printf("Size: %lld\n", set_size(set));
    set_add(set, &d1);
    printf("Size: %lld\n", set_size(set));
    set_add(set, &d2);
    printf("Size: %lld\n", set_size(set));

    for (set_iter_t it = set_begin(set); !set_end(set, it); it = set_next(set, it)) {
        struct data d;
        set_get(set, it, &d);
        print_data(&d);
    }

}