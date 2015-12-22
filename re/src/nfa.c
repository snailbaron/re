#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "nfa.h"

typedef unsigned int nfa_state_t;
typedef char sym_t;
typedef struct nfa_trans_t nfa_trans_t;
typedef struct list_item_t list_item_t;
typedef struct nfa_fin_state_t nfa_fin_state_t;
typedef struct nfa_lst_t nfa_lst_t;
typedef struct nfa_t nfa_t;

struct list_item_t
{
    list_item_t *next;
};

struct nfa_trans_t
{
    nfa_state_t start;
    sym_t sym;
    nfa_state_t end;
    list_item_t list;
};

struct nfa_fin_state_t
{
    nfa_state_t state;
    list_item_t list;
};

struct nfa_t
{
    nfa_state_t state_count;
    nfa_state_t start;
    list_item_t trans_table;
    list_item_t fin_states;
};

struct nfa_lst_t
{
    nfa_state_t state;
    list_item_t list;
};

nfa_t * nfa_create()
{
    nfa_t *nfa = malloc(sizeof(nfa_t));
    nfa->state_count = 0;
    nfa->start = 0;
    nfa->trans_table.next = NULL;
    nfa->fin_states.next = NULL;
    return nfa;
}

nfa_state_t nfa_add_state(nfa_t *nfa, const char *name)
{
    nfa->state_count++;
    return nfa->state_count;
}

void nfa_set_start(nfa_t *nfa, nfa_state_t state)
{
    nfa->start = state;
}

void nfa_set_finish(nfa_t *nfa, nfa_state_t state)
{
    list_item_t *p = &nfa->fin_states;
    while (p->next != NULL) {
        p = p->next;
    }
    nfa_fin_state_t *fin = malloc(sizeof(nfa_fin_state_t));
    fin->list.next = NULL;
    fin->state = state;
    p->next = &fin->list;
}

void nfa_link(nfa_t *nfa, nfa_state_t start, nfa_state_t end, sym_t sym)
{
    list_item_t *p = &nfa->trans_table;
    while (p->next != NULL) {
        p = p->next;
    }
    nfa_trans_t *trans = malloc(sizeof(nfa_trans_t));
    trans->start = start;
    trans->end = end;
    trans->sym = sym;
    trans->list.next = NULL;
    p->next = &trans->list;
}

