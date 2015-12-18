#ifndef _map_H_
#define _map_H_

typedef struct map_t map_t;

typedef int (*map_comparator_t)(void *left, void *right);

map_t * map_create(size_t key_size, size_t value_size, map_comparator_t comparator);
void map_kill(map_t *map);

void map_set(map_t *map, void *key, void *value);
void * map_pget(map_t *map, void *key);
void map_get(map_t *map, void *key, void *dst);

#endif
