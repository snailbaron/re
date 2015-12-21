#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"

typedef struct node_t node_t;

/**
 * Node of a list
 */
struct node_t
{
    node_t *next;       // pointer to next node in list
    char value[];       // value holded by this node
};

/**
 * List
 */
struct list_t
{
    /** Pointer to first node of the list */
    node_t *head;

    /** Size of elements each node is holding */
    size_t elsize;
};

static node_t * _create_node(list_t *list, void *value, node_t *next)
{
    node_t *node = malloc(sizeof(node_t) + list->elsize);
    node->next = next;
    memcpy(node->value, value, list->elsize);
    return node;
}

list_t * list_create_by_size(size_t element_size)
{
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->elsize = element_size;
    return list;
}

void list_kill(list_t *list)
{
    assert(list);
    
    node_t *p = list->head;
    while (p) {
        node_t *next = p->next;
        free(p);
        p = next;
    }
    free(list);
}

struct list_iter_t
{
    list_t *list;
    node_t *ptr;
    node_t **ref_ptr;
};

list_iter_t * list_start_iter(list_t *list)
{
    list_iter_t *it = malloc(sizeof(list_iter_t));
    it->list = list;
    it->ptr = list->head;
    it->ref_ptr = &list->head;
    return it;
}

void list_end_iter(list_iter_t *it)
{
    free(it);
}

void list_next(list_iter_t *it)
{
    *it->ref_ptr = it->ptr;
    it->ptr = it->ptr->next;
}

bool list_end(list_iter_t *it)
{
    return (it->ptr == NULL);
}

void * list_pget(list_iter_t *it)
{
    return it->ptr->value;
}

void list_get(list_iter_t *it, void *dst)
{
    memcpy(dst, list_pget(it), it->list->elsize);
}

void list_add(list_iter_t *it, void *value)
{
    node_t *node = _create_node(it->list, value, it->ptr);
    *it->ref_ptr = node;
    it->ptr = node;
}

void list_rm(list_iter_t *it)
{
    assert(it->ptr);
    *it->ref_ptr = it->ptr->next;
    free(it->ptr);
    it->ptr = it->ptr->next;
}