#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node_t node_t;

struct map_t
{
    size_t key_size;
    size_t value_size;
    node_t *root;
    int (*compare)(void *left, void *right);
};

struct node_t
{
    void *key;
    void *value;
    node_t *parent;
    node_t *left;
    node_t *right;
};

static void _set_key(map_t *map, node_t *node, void *key)
{
    memcpy(node->key, key, map->key_size);
}

static void _set_value(map_t *map, node_t *node, void *value)
{
    memcpy(node->value, value, map->value_size);
}

static node_t * _create_node(map_t *map, node_t *parent, node_t *left, node_t *right, void *key, void *value)
{
    node_t *node = malloc(sizeof(node_t));
    node->parent = parent;
    node->left = left;
    node->right = right;
    _set_key(map, node, key);
    _set_value(map, node, value);
    return node;
}

static void _kill_node(node_t *node)
{
    assert(node->key && node->value);
    free(node->key);
    free(node->value);
    free(node);
}

static void _kill_node_tree(node_t *node)
{
    if (node) {
        if (node->left) {
            _kill_node_tree(node->left);
        }
        if (node->right) {
            _kill_node_tree(node->right);
        }
        _kill_node(node);
    }
}

map_t * map_create(size_t key_size, size_t value_size, map_comparator_t comparator)
{
    map_t *map = malloc(sizeof(map_t));
    map->key_size = key_size;
    map->value_size = value_size;
    map->root = NULL;
    map->compare = comparator;
    return map;
}

void map_kill(map_t *map)
{
    _kill_node_tree(map->root);
    free(map);
}

void map_set(map_t *map, void *key, void *value)
{
    node_t *parent = NULL;
    node_t *cur = map->root;
    
    int comp_result = 0;
    while (cur) {
        comp_result = map->compare(key, cur->key);

        if (comp_result == 0) {
            _set_value(map, cur, value);
            return;
        } else if (comp_result < 0) {
            parent = cur;
            cur = cur->left;
        } else if (comp_result > 0) {
            parent = cur;
            cur = cur->right;
        }
    }
    
    node_t *node = _create_node(map, parent, NULL, NULL, key, value);
    if (comp_result < 0) {
        parent->left = node;
    } else if (comp_result > 0) {
        parent->right = node;
    }

    // TODO: Balance after insert
}

void * map_pget(map_t *map, void *key)
{
    node_t *cur = map->root;

    while (cur) {
        int comp_result = map->compare(key, cur->key);

        if (comp_result == 0) {
            return cur->value;
        } else if (comp_result < 0) {
            cur = cur->left;
        } else if (comp_result > 0) {
            cur = cur->right;
        }
    }
     
    return NULL;   
}

void map_get(map_t *map, void *key, void *dst)
{
    void *pres = map_pget(map, key);
    if (pres) {
        memcpy(pres, dst, map->value_size);
    }
}

