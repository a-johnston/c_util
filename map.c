#ifndef __C_MAP_UTIL

#define __C_MAP_UTIL

#include "util.h"

#define MAX_OFFSET 5

// src: djb2 http://www.cse.yorku.ca/~oz/hash.html
static int _hash(char *str) {
    int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static char* _copy_key(char *key) {
    char *copy = (char*) calloc(strlen(key) + 1, sizeof(char));
    strcpy(copy, key);
    return copy;
}

static int _try_put(Map *map, struct map_element e, int hash, int offset) {
    int i  = (hash + offset) % map->size;
    struct map_element old = map->data[i];

    if (old.value) {
        return 0;
    }

    map->data[i] = e;
    return 1;
}

static void _resize_map(Map*);

static void _put(Map *map, struct map_element e) {
    int hash = _hash(e.key);
    for (int i = 0; i < MAX_OFFSET; i++) {
        if (_try_put(map, e, hash, i)) {
            return;
        }
    }

    _resize_map(map);
    _put(map, e);
}

static void _resize_map(Map *map) {
    struct map_element *old = map->data;
    struct map_element *new = (struct map_element*) calloc(map->size * 2, sizeof(struct map_element));

    int old_size = map->size;

    *map = (Map) {
        .data = new,
        .size = old_size * 2
    };

    struct map_element e;
    for (int i = 0; i < old_size; i++) {
        e = old[i];
        _put(map, e);
    }

    free(old);
}

Map* map_create() {
    Map *map = (Map*) malloc(sizeof(Map));

    *map = (Map) {
        .data = (struct map_element*) calloc(DEFAULT_CAPACITY, sizeof(struct map_element)),
        .size = DEFAULT_CAPACITY
    };

    return map;
}

void map_free(Map *map) {
    free(map->data);
    free(map);
}

void map_put(Map *map, char *key, void *value) {
    struct map_element e = (struct map_element) {
        .key   = _copy_key(key),
        .value = value
    };
    _put(map, e);
}

void map_get(Map *map, char *key) {

}

#endif