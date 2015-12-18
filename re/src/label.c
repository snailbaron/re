#include "label.h"
#include <assert.h>
#include <string.h>

struct label_t {
    char *data;
    size_t size;
    size_t buf_len;
};

label_t * label_create()
{
    label_t *label = malloc(sizeof(label_t));
    label->data = malloc(100);
    label->data[0] = '\0';
    label->size = 0;
    label->buf_len = 100;
    return label;
}

void label_kill(label_t *label)
{
    assert(label);
    assert(label->data);
    free(label->data);
}

// Extend label to be able to hold a string of 'size' length.
// Does nothing, if the label is already capable of it.
void label_extend(label_t *label, size_t size)
{
    if (label->buf_len < size + 1) {
        do {
            label->buf_len *= 2;
        } while (label->buf_len < size + 1);
        label->data = realloc(label->data, label->buf_len);
    }
}

void label_set(label_t *label, const char *str)
{
    size_t str_len = strlen(str);
    label_extend(label, str_len);
    strcpy_s(label->data, label->buf_len, str);
    label->size = str_len;
}

size_t label_size(const label_t *label)
{
    return label->size;
}

const char * label_str(const label_t *label)
{
    return label->data;
}

void label_append_str_with_len(label_t *label, const char *str, size_t str_len)
{
    size_t len_sum = label->size + str_len;
    label_extend(label, len_sum);
    //strcpy_s(label->data + label->size, label->buf_len - label->size, str);
    char *dst = label->data + label->size;
    const char *src = str;
    while (*dst++ = *src++);
    label->size = len_sum;
}

void label_append_str(label_t *label, const char *str)
{
    label_append_str_with_len(label, str, strlen(str));
}

void label_append(label_t *label, const label_t *appendix)
{
    label_append_str_with_len(label, label_str(appendix), label_size(appendix));
}

