#ifndef __C_LIST_UTIL

#define __C_LIST_UTIL

#include "util.h"

static int int_mod(int i, int m) {
    if (i >= 0) {
        return i % m;
    } else {
        return m + (i % m);
    }
}

static void _realloc_data(List *list) {
    void *temp = realloc(list->data, list->element_size * list->capacity);

    if (temp != list->data) {
        list->data = temp;
    }
}

static void _ensure_capacity(List *list, int length, int buffer, float scale) {
    if (list->capacity < length) {
        list->capacity = (int) ((length + buffer) * scale);
        _realloc_data(list);
    }
}

static void _add(List *list, void *e) {
    memcpy(list->data + list->element_size * list->length, e, list->element_size);
    list->length++;
}

List* _list_create(int element_size) {
    List *list = (List*) malloc(sizeof(List));

    *list = (List) {
        NULL,
        element_size,
        0,
        DEFAULT_CAPACITY
    };
    _realloc_data(list);

    return list;
}

void list_add_p(List *list, void *e) {
    _ensure_capacity(list, list->length + 1, DEFAULT_CAPACITY, 1.5f);
    _add(list, e);
}

void list_add_all(List *list, ...) {
    va_list args;
    void *arg;
    va_start(args, list);

    while ((arg = va_arg(args, void*)) != NULL) {
        list_add_p(list, arg);
    }

    va_end(args);
}

void* list_get_p(List *list, int i) {
    return list->data + list->element_size * int_mod(i, list->length);
}

int list_find_p(List *list, void* pointer) {
    for (int i = 0; i < list->length; i++) {
        if (memcmp(list->data + i * list->element_size, pointer, list->element_size) == 0) {
            return i;
        }
    }
    return -1;
}

void list_remove(List *list, int i) {
    i = int_mod(i, list->length);
    void *p = list->data + i * list->element_size;
    memmove(p, p + list->element_size, list->element_size * (list->length - i - 1));
    list->length--;
}

#endif
