#ifndef _NFA_H_
#define _NFA_N_

#include <stdbool.h>

typedef char sym_t;
typedef struct nfa_t nfa_t;
typedef struct nfa_state_t nfa_state_t;

typedef enum
{
    NFA_YES,
    NFA_NO,
    NFA_ERROR,
} nfa_run_result_t;

nfa_t * nfa_create();
nfa_state_t * nfa_create_state(const char *name);
nfa_state_t * nfa_create_start_state(nfa_t *nfa, const char *name);
void nfa_set_start(nfa_t *nfa, nfa_state_t *state);
void nfa_link(nfa_state_t *start, nfa_state_t *end, sym_t sym);
void nfa_set_finish(nfa_state_t *state, bool finish);

#endif
