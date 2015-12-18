#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct stack_t
{
    void *data;
    size_t elsize;
    size_t cap;
    size_t size;
};

static void _extend(stack_t *stack)
{
    stack->cap *= 2;
    stack->data = realloc(stack->data, stack->cap);
}

stack_t * stack_create_by_size(size_t element_size)
{
    stack_t *stack = malloc(sizeof(stack_t));
    stack->data = malloc(element_size);
    stack->elsize = element_size;
    stack->cap = 1;
    stack->size = 0;
    return stack;
}

void stack_kill(stack_t *stack)
{
    assert(stack && stack->data);
    free(stack->data);
    free(stack);
}

bool stack_empty(stack_t *stack)
{
    return (stack->size == 0);
}

void stack_push(stack_t *stack, void *addr)
{
    if (stack->size == stack->cap) {
        _extend(stack);
    }
    memcpy((char *)stack->data + stack->elsize * stack->size, addr, stack->elsize);
    stack->size++;
}

void stack_pop(stack_t *stack, void *dst)
{
    assert(!stack_empty(stack));
    memcpy(dst, (char *)stack->data + stack->elsize * (stack->size - 1), stack->elsize);
    stack->size--;
}