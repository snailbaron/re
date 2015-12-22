#include "set.h"
#include "list.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define HASH_VALUE_COUNT 256
#define HASH_VALUE_MAX 255

struct set_t
{
    list_t *table[HASH_VALUE_COUNT];
    size_t elsize;
};

hash_t _hash(set_t *set, void *value)
{
    char *bytes = value;
    hash_t hash = 0;
    for (size_t i = 0; i < set->elsize; i++) {
        hash += bytes[i];
    }
    return hash;
}

bool _value_eq(set_t *set, void *val1, void *val2)
{
    return (strncmp(val1, val2, set->elsize) == 0);
}

set_t * set_create_by_size(size_t element_size)
{
    set_t *set = malloc(sizeof(set_t));
    for (size_t i = 0; i < HASH_VALUE_COUNT; i++) {
        set->table[i] = list_create_by_size(element_size);
    }
    set->elsize = element_size;
    return set;
}

void set_kill(set_t *set)
{
    for (size_t i = 0; i < HASH_VALUE_COUNT; i++) {
        list_kill(set->table[i]);
    }
    free(set);
}

void set_insert(set_t *set, void *value)
{
    hash_t hash = _hash(set, value);
    list_iter_t it = list_find(set->table[hash], value);
    if (list_done(&it)) {
        list_insert(&it, value);
    }
}

void set_rm(set_t *set, void *value)
{
    hash_t hash = _hash(set, value);
    list_iter_t it = list_find(set->table[hash], value);
    if (!list_done(&it)) {
        list_rm(&it);
    }
}

set_iter_t set_first(set_t *set)
{
    set_iter_t it;
    it.set = set;

    hash_t hash = 0;
    while (hash < HASH_VALUE_MAX && list_empty(set->table[hash])) {
        hash++;
    }
    it.hash = hash;

    it.it = list_first(set->table[hash]);
    
    return it;
}

bool set_done(set_iter_t *it)
{
    return (list_done(&it->it));
}

void set_next(set_iter_t *it)
{
    list_next(&it->it);
    if (list_done(&it->it)) {
        hash_t hash = it->hash;
        if (hash < HASH_VALUE_MAX) {
            hash++;
        }
        while (hash < HASH_VALUE_MAX && list_empty(it->set->table[hash])) {
            hash++;
        }
        it->hash = hash;
        it->it = list_first(it->set->table[hash]);
    }
}

void * set_pget(set_iter_t *it)
{
    return list_pget(&it->it);
}

void set_get(set_iter_t *it, void *dst)
{
    list_get(&it->it, dst);
}