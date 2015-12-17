#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dfa.h"

typedef long state_t;
typedef unsigned char sym_t;

#define MAX_STATES 100
#define MAX_FIN_STATES MAX_STATES
#define SYM_NUM 200
#define MAX_NAME_LEN 100

#define NO_STATE 0

struct dfa_t {
    state_t trans_table[MAX_STATES][SYM_NUM];
    state_t start;
    unsigned char fin_mask[(MAX_STATES - 1) / CHAR_BIT + 1];
    state_t state_count;
    char state_names[MAX_STATES][MAX_NAME_LEN + 1];
    unsigned char sym_table[MAX_STATES][MAX_STATES][(SYM_NUM - 1) / CHAR_BIT + 1];
};

dfa_t * dfa_create()
{
    dfa_t *dfa = malloc(sizeof(dfa_t));
    memset(dfa->trans_table, 0, MAX_STATES * SYM_NUM * sizeof(state_t));
    dfa->start = NO_STATE;
    memset(dfa->fin_mask, 0, (MAX_STATES - 1) / CHAR_BIT + 1);
    dfa->state_count = 0;
    memset(dfa->sym_table, 0, MAX_STATES * MAX_STATES * ((SYM_NUM - 1) / CHAR_BIT + 1));
    return dfa;
}

state_t dfa_create_state(dfa_t *dfa)
{
    dfa->state_count++;
    return dfa->state_count;
}

void dfa_set_start(dfa_t *dfa, state_t state)
{
    dfa->start = state;
}

void dfa_set_finish(dfa_t *dfa, state_t state, bool finish)
{
    unsigned char *byte = dfa->fin_mask + state / CHAR_BIT;
    if (finish) {
        *byte |= (1 << state % CHAR_BIT);
    } else {
        *byte &= ~(1 << state % CHAR_BIT);
    }
}

void dfa_link(dfa_t *dfa, state_t q_start, state_t q_end, sym_t sym)
{
    dfa->trans_table[q_start][sym] = q_end;
    unsigned char *byte = dfa->sym_table[q_start][q_end] + sym / CHAR_BIT;
    *byte |= (1 << sym % CHAR_BIT);
}

bool dfa_run(dfa_t *dfa, sym_t *str, size_t str_len)
{
    state_t state = dfa->start;
    for (size_t i = 0; i < str_len; i++) {
        state = dfa->trans_table[state][str[i]];
    }

    if (dfa->fin_mask[state / CHAR_BIT] & (1 << state % CHAR_BIT)) {
        return true;
    }

    return false;
}

void dfa_name_state(dfa_t *dfa, state_t state, const char *name)
{
    strcpy_s(dfa->state_names[state], MAX_NAME_LEN + 1, name);
}

void dfa_gen_dot(dfa_t *dfa, const char *fname)
{
    FILE *outfile = NULL;
    if (fopen_s(&outfile, fname, "w")) {
        return;
    }

    fprintf(outfile, "digraph {\n");
    fprintf(outfile, "    rankdir=LR\n");
    fprintf(outfile, "    node [shape=circle]\n");
    fprintf(outfile, "\n");

    for (state_t s = 1; s <= dfa->state_count; s++) {
        if (s == dfa->start) {
            fprintf(outfile, "    q%ld [label=\"%s\", shape=doublecircle]\n", s-1, dfa->state_names[s]);
        } else {
            fprintf(outfile, "    q%ld [label=\"%s\"]\n", s-1, dfa->state_names[s]);
        }
    }
    fprintf(outfile, "\n");

    for (state_t start = 1; start <= dfa->state_count; start++) {
        for (state_t end = 1; end <= dfa->state_count; end++) {
            bool found = false;
            for (sym_t sym = 0; sym < SYM_NUM; sym++) {
                if (dfa->sym_table[start][end][sym / CHAR_BIT] & (1 << sym % CHAR_BIT)) {
                    if (!found) {
                        fprintf(outfile, "    q%ld -> q%ld [label = \"", start-1, end-1);
                        found = true;
                    } else {
                        fprintf(outfile, ",");
                    }
                    fprintf(outfile, "%c", sym);
                }
            }
            if (found) {
                fprintf(outfile, "\"]\n");
            }
        }
    }

    fprintf(outfile, "}\n");

    fclose(outfile);
}

state_t dfa_create_named_state(dfa_t *dfa, const char *name)
{
    state_t st = dfa_create_state(dfa);
    dfa_name_state(dfa, st, name);
    return st;
}

void dfa_kill(dfa_t *dfa)
{
}