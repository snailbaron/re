#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct htable_t htable_t;

typedef bool (*key_comp_t)(void *left_key, void *right_key);

typedef uint8_t hash_t;

#define INITIAL_ROW_NUM 1000

struct htable_t
{
    size_t key_size;
    size_t value_size;
    key_comp_t compare;
    void *data;
    size_t row_num;
};

void * _get_row(htable_t *ht, size_t row_num)
{
    return (char *)ht->data + (ht->key_size + ht->value_size) * row_num;
}

void * _get_row_key(htable_t *ht, void *row)
{
    return (char *)row;
}

void * _get_row_value(htable_t *ht, void *row)
{
    return (char *)row + ht->key_size;
}

hash_t _hash(htable_t *ht, void *key)
{
    unsigned char *bytes = key;
    hash_t hash = 0;
    for (size_t i = 0; i < ht->key_size; i++) {
        hash += bytes[i];
    }
    return hash;
}

void _extend(htable_t *ht)
{
    ht->row_num *= 2;
    ht->data = realloc(ht->data, ht->row_num);
}

htable_t * htable_create_by_size(size_t key_size, size_t value_size, key_comp_t comparator)
{
    htable_t *ht = malloc(sizeof(htable_t));
    ht->key_size = key_size;
    ht->value_size = value_size;
    ht->compare = comparator;
    ht->data = malloc((key_size + value_size + sizeof(bool)) * INITIAL_ROW_NUM);
    ht->row_num = INITIAL_ROW_NUM;
    return ht;
}

void htable_kill(htable_t *htable)
{
    free(htable->data);
    free(htable);
}

void htable_set(htable_t *htable, void *key, void *value)
{
    hash_t hash = _hash(htable, key);
    
        

}