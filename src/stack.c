#include <stdio.h>
#include <stdlib.h>

struct stack {
    int * elements;
    int size;
    int max_size;
};

void stack_init(struct stack * s, int size) {
    s->size = 0;
    s->max_size = size;
    s->elements = malloc(size * sizeof (int));
}

void stack_destroy(struct stack * s) {
    free(s->elements);
}

int stack_push(struct stack * s, int item) {
    if (s->size == s->max_size) {
        return -1;
    }
    s->elements[s->size++] = item;
    return 0;
}

int stack_pop(struct stack * s) {
    if (s->size == 0)
        return -1;
    return s->elements[--s->size];
}

int main() {

    struct stack s;
    stack_init(&s, 10);

    stack_push(&s, 3);
    stack_push(&s, 2);
    stack_push(&s, 1);

    int i;
    while ((i = stack_pop(&s)) != -1) {
        /* Prints 1, 2, 3 */
        printf("Element: %d\n", i);
    }

    return 0;

}
