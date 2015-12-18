#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct set_t
{
    void *data;
    size_t elsize;
    size_t cap;
    size_t size;
};

void * _addr(set_t *set, size_t idx)
{
    return (char *)set->data + set->elsize * idx;
}

void _extend(set_t *set)
{
    set->cap = set->cap * 2;
    set->data = realloc(set->data, set->elsize * set->cap);
}

set_t * set_create(size_t element_size)
{
    set_t *set = malloc(sizeof(set_t));
    set->data = malloc(element_size);
    set->elsize = element_size;
    set->cap = 1;
    set->size = 0;
    return set;
}

void set_kill(set_t *set)
{
    assert(set && set->data);
    free(set->data);
    free(set);
}

size_t set_size(set_t *set)
{
    return set->size;
}

void set_add(set_t *set, void *data)
{
    if (set->size == set->cap) {
        _extend(set);
    }

    void *dst = _addr(set, set->size);
    memcpy(dst, data, set->elsize);
    set->size++;
}

set_iter_t set_begin(set_t *set)
{
    set_iter_t it = { .idx = 0 };
    return it;
}

bool set_end(set_t *set, set_iter_t iter)
{
    return (iter.idx >= set->size);
}

set_iter_t set_next(set_t *set, set_iter_t iter)
{
    set_iter_t next = iter;
    if (next.idx < set->size) {
        next.idx++;
    }
    return next;
}

void set_get(set_t *set, set_iter_t iter, void *dst)
{
    if (!set_end(set, iter)) {
        memcpy(dst, _addr(set, iter.idx), set->elsize);
    }
}

void * set_pget(set_t *set, set_iter_t iter)
{
    if (set_end(set, iter)) {
        return NULL;
    }
    return _addr(set, iter.idx);
}

void set_rm(set_t *set, set_iter_t iter)
{
    assert(!set_end(set, iter));

    if (iter.idx < set->size - 1) {
        memcpy(_addr(set, iter.idx), _addr(set, set->size-1), set->elsize);
    }
    set->size--;
}

