#include <stdio.h>
#include <stdlib.h>

struct queue {
    int * item_base;
    int offset;
    int size;
    int max_size;
};

void queue_init(struct queue * q, int size) {
    q->size = 0;
    q->max_size = size;
    q->offset = 0;
    q->item_base = malloc(size * sizeof(int));
}

void queue_destroy(struct queue * q) {
    free(q->item_base);
}

#define Q_ELEM_AT(q, loc) (q->item_base[(q->offset + (loc)) % q->max_size])

int queue_add(struct queue * q, int item) {
    if (q->size == q->max_size) {
        return -1;
    }
    Q_ELEM_AT(q, q->size++) = item;
    return 0;
}

int queue_poll(struct queue * q) {
    if (q->size == 0) {
        return -1;
    }
    int ret = Q_ELEM_AT(q, 0);
    ++q->offset;
    --q->size;
    return ret;
}

int main() {

    struct queue q;
    queue_init(&q, 10);

    queue_add(&q, 1);
    queue_add(&q, 2);
    queue_add(&q, 3);

    int i;
    while ((i = queue_poll(&q)) != -1) {
        /* 1, 2, 3 */
        printf("Element: %d\n", i);
    }

}
