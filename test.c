#include <stdio.h>

#include "list.c"
#include "map.c"

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

    list_insert(list, 2, SomeStruct, ss);

    for (int i = 0; i < list->length; i++) {
        ss = list_get(list, SomeStruct, i);

        printf("%d : %d %f\n", i, ss.x, ss.y);
    }

    foreach (ss, list) {
        printf("foreach %d : %d %f\n", i, ss.x, ss.y);
    }

    list_free(list);

    Map *map = map_create();

    int x = 123123;
    int y = 321321;

    map_put(map, "key1", &y);
    map_put(map, "key1", &x);

    map_put(map, "key2", &x);
    map_put(map, "key3", &x);
    map_put(map, "key4", &x);
    map_put(map, "key5", &x);
    map_put(map, "key6", &x);
    map_put(map, "key7", &x);
    map_put(map, "key8", &x);
    map_put(map, "key9", &x);
    map_put(map, "key10", &x);
    map_put(map, "key11", &x);
    map_put(map, "key12", &x);
    map_put(map, "key13", &x);

    y = *(int*) map_get(map, "key1");

    printf("Map put and get: %d %d\n", x, y);

    map_free(map);
}
