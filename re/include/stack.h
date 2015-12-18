#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct stack_t stack_t;

stack_t * stack_create_by_size(size_t element_size);

#define stack_create(TYPE) stack_create_by_size(sizeof(TYPE))

void stack_kill(stack_t *stack);

bool stack_empty(stack_t *stack);

void stack_push(stack_t *stack, void *addr);

void stack_pop(stack_t *stack, void *dst);

#endif
