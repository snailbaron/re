#ifndef _SET_H_
#define _SET_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct set_t set_t;

// Create a new set of elements of a certain size
set_t * set_create(size_t element_size);

// Free existing set
void set_kill(set_t *set);

// Add an element to set by its address
void set_add(set_t *set, void *data);

// Get number of elements in set
size_t set_size(set_t *set);


/* Iterators */

// Iterator structure
typedef struct
{
    size_t idx;
} set_iter_t;

// Begin iterating a set
set_iter_t set_begin(set_t *set);

// Check if finished iterating a set
bool set_end(set_t *set, set_iter_t iter);

// Get next element of a set
set_iter_t set_next(set_t *set, set_iter_t iter);

// Copy value of current element to a location
void set_get(set_t *set, set_iter_t iter, void *dst);

// Get pointer to current element
void * set_pget(set_t *set, set_iter_t iter);

// Remove element from set
void set_rm(set_t *set, set_iter_t iter);

#endif
