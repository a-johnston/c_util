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

#define element(type, x) type x; memset(&x, 0, sizeof(type))

#define list_create(type_t) (_list_create(sizeof(type_t)))

#define list_add(l, type_t, e) do {type_t temp = e; list_add_p(l, &temp);} while (0)

#define list_get(l, type_t, i) (*(type_t*)list_get_p(l, i))

List* _list_create(int);

void list_add_p(List*, void*);

void list_add_all(List*, ...);

void* list_get_p(List*, int);

int list_find_p(List*, void*);

void list_remove(List*, int);

#endif
