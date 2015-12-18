#ifndef _LABEL_H_
#define _LABEL_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct label_t label_t;

// Create a new label
label_t * label_create();

// Remove an existing label
void label_kill(label_t *label);

// Set a new value for label
void label_set(label_t *label, const char *str);

// Get label length
size_t label_size(const label_t *label);

// Get label value as a C-string
const char * label_str(const label_t *label);

// Append a C-string to a label
void label_append_str(label_t *label, const char *str);

// Append one label to another
void label_append(label_t *label, const label_t *appendix);

#ifdef __cplusplus
}
#endif


#endif
