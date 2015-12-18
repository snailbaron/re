#include "nfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RULES 2
#define MAX_SYMS 100
#define MAX_NAME_LEN 100
#define MAX_PARALLEL_STATES 100

size_t sym_index(sym_t sym)
{
    return sym - 'a' + 1;
}

struct nfa_t
{
    nfa_state_t *start;
};

struct nfa_state_t
{
    bool finish;
    char name[MAX_NAME_LEN + 1];
    nfa_state_t *outs[MAX_RULES][MAX_SYMS];
    size_t rule_count;
};

nfa_t * nfa_create()
{
    nfa_t *nfa = malloc(sizeof(nfa_t));
    nfa->start = NULL;
    return nfa;
}

nfa_state_t * nfa_create_state(const char *name)
{
    nfa_state_t *state = malloc(sizeof(nfa_state_t));
    state->finish = false;
    strncpy_s(state->name, MAX_NAME_LEN + 1, name, MAX_NAME_LEN);
    for (size_t i = 0; i < MAX_RULES; i++) {
        for (size_t j = 0; j < MAX_SYMS; j++) {
            state->outs[i][j] = NULL;
        }
    }
    state->rule_count = 0;
    
    return state;
}

void nfa_set_start(nfa_t *nfa, nfa_state_t *state)
{
    nfa->start = state;
}

nfa_state_t * nfa_create_start_state(nfa_t *nfa, const char *name)
{
    nfa_state_t *state = nfa_create_state(name);
    nfa_set_start(nfa, state);
    return state;
}

void nfa_set_finish(nfa_state_t *state, bool finish)
{
    state->finish = finish;
}

void nfa_link(nfa_state_t *start, nfa_state_t *end, sym_t sym)
{
    start->outs[start->rule_count++][sym] = end;
}

nfa_run_result_t nfa_run(nfa_t *nfa, sym_t *input, size_t input_len)
{
    nfa_state_t *current[MAX_PARALLEL_STATES];
    size_t state_count = 0;

    state_count = 1;
    current[0] = nfa->start;

    
    return NFA_ERROR; 
}