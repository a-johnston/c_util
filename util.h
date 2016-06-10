#ifndef __C_LIST_UTIL_H

#define __C_LIST_UTIL_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 10

/*
 * list.c
 */

typedef struct {
    void *data;
    int element_size;
    int length;
    int capacity;
} List;

//#define each(t, x, list) (int i = 0; (x = *(t*)list_get_p(list, i)), i < list->length; i++)

#define each(x) (long _i = 0, _p = (long) &x;

#define in(list) ((memcpy((void*) _p, list_get_p(list, _i), list->element_size))), _i < list->length; _i++)

#define element(type, x) type x; memset(&x, 0, sizeof(type))

#define list_create(type_t) (_list_create(sizeof(type_t)))

#define list_add(l, type_t, e) do {type_t temp = e; list_add_p(l, &temp);} while (0)

#define list_insert(l, i, type_t, e) do {type_t temp = e; list_insert_p(list, i, &temp);} while(0)

#define list_get(l, type_t, i) (*(type_t*)list_get_p(l, i))

List* _list_create(int);

void list_free(List*);

void list_add_p(List*, void*);

void list_add_all(List*, ...);

void* list_get_p(List*, int);

int list_find_p(List*, void*);

void list_insert_p(List*, int, void*);

void list_remove(List*, int);

void list_set_capacity(List*, int);

void _list_put(List*, int, void*);

/*
 * map.c
 */

struct map_element {
    char *key;
    void *value;
};

typedef struct {
    struct map_element *data;
    int size;
} Map;

Map* map_create();

void map_free(Map*);

void map_put(Map*, char*, void*);

void* map_get(Map*, char*);

void map_remove(Map*, char*);

List* map_get_values(Map*);

#endif
