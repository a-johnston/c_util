#include <stdio.h>

#include "list.c"

typedef struct {
    int x;
    double y;
} SomeStruct;

int main() {
    List *list = list_create(SomeStruct);
    element(SomeStruct, ss);

    list_add_all(list, &ss, &ss, &ss, NULL);

    for (int i = 0; i < 10; i++) {
        ss.x = i;
        ss.y = i / 2.0;

        list_add_p(list, &ss);
    }

    printf("Length: %d\n", list->length);

    ss = list_get(list, SomeStruct, 1);
    printf("Second element: (%d, %f)\n", ss.x, ss.y);

    ss.x = 5;
    ss.y = 5 / 2.0;

    int whereis = list_find_p(list, &ss);

    list_remove(list, whereis);

    ss.x = 123;
    ss.y = 3.33;

    list_insert_p(list, 2, &ss);

    for (int i = 0; i < list->length; i++) {
        ss = list_get(list, SomeStruct, i);

        printf("%d : %d %f\n", i, ss.x, ss.y);
    }

    list_free(list);
}
