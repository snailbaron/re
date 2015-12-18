#ifndef _DFA_H_
#define _DFA_H_

#include <stdbool.h>
#include <stdlib.h>

typedef long state_t;
typedef unsigned char sym_t;

typedef struct dfa_t dfa_t;

dfa_t * dfa_create();
state_t dfa_create_state(dfa_t *dfa);
void dfa_set_start(dfa_t *dfa, state_t state);
void dfa_link(dfa_t *dfa, state_t q_start, state_t q_end, sym_t sym);
bool dfa_run(dfa_t *dfa, sym_t *str, size_t str_len);
void dfa_set_finish(dfa_t *dfa, state_t state, bool finish);
void dfa_name_state(dfa_t *dfa, state_t state, const char *name);
void dfa_gen_dot(dfa_t *dfa, const char *fname);
state_t dfa_create_named_state(dfa_t *dfa, const char *name);
void dfa_kill(dfa_t *dfa);

#endif
