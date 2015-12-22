/**
 @file

 Set functionality
*/

#ifndef _SET_H_
#define _SET_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "list.h"

typedef struct set_t set_t;

set_t * set_create_by_size(size_t element_size);

#define set_create(TYPE) set_create_by_size(sizeof(TYPE))

void set_kill(set_t *set);

void set_insert(set_t *set, void *value);

void set_rm(set_t *set, void *value);



typedef uint8_t hash_t;

typedef struct set_iter_t set_iter_t;

struct set_iter_t
{
    set_t *set;
    hash_t hash;
    list_iter_t it;
};

set_iter_t set_first(set_t *set);

bool set_done(set_iter_t *it);

void set_next(set_iter_t *it);

void * set_pget(set_iter_t *it);

void set_get(set_iter_t *it, void *dst);


#endif
