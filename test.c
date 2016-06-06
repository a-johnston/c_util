#include <stdio.h>

#include "list.c"

typedef struct {
    int x;
    double y;
} SomeStruct;

int main() {
    List *list = list_create(SomeStruct);
    SomeStruct ss;
    for (int i = 0; i < 1000; i++) {
        ss = (SomeStruct) {
            i,
            i / 2.0
        };
        list_add_p(list, &ss);
    }

    printf("Length: %d\n", list->length);

    ss = list_get(list, SomeStruct, 1);
    printf("Second element: (%d, %f)\n", ss.x, ss.y);

    ss = (SomeStruct) {
        10,
        5.0
    };
    printf("Where is (10, 5.0): %d\n", list_find_p(list, &ss));
}
