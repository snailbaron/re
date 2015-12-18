#include "nfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

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
    set_t *cur = set_create(nfa_state_t *);
    set_add(cur, nfa->start);

    set_t *next = set_create(nfa_state_t *);

    // Read input one character at a time
    for (size_t i = 0; i < input_len; i++) {
        set_clear(next);

        // Move each of the current states
        for (set_iter_t it = set_begin(cur); set_size(cur) > 0; set_rm(cur, it)) {
            nfa_state_t *ps = set_pget(cur, it);
            
            // Move the state using all applicable rules
            for (size_t j = 0; j < ps->rule_count; j++) {
                if (ps->outs[j][sym_index(input[i])] != NULL) {
                    set_add(next, ps->outs[j][sym_index(input[i])]);
                }
            }
        }

        set_kill(cur);
        cur = next;
        next = set_create(nfa_state_t);
    }
    set_kill(next);

    bool yes = false;
    for (set_iter_t it = set_begin(cur); !set_end(cur, it); it = set_next(cur, it)) {
        nfa_state_t *ps = set_pget(cur, it);
        if (ps->finish) {
            yes = true;
            break;
        }
    }
    set_kill(cur);

    if (yes) {
        return NFA_YES;
    } else {
        return NFA_NO;
    }
}