#include <stdio.h>
#include <stdlib.h>
#define COUNT 1000000

unsigned int fnv1a(char *string);

struct Value {
    char *data;
};

struct Pair {
    size_t id;
    char *key;
    struct Value *value;
};

struct Hashmap {
    struct Pair **buckets;
    size_t size;
};

struct Value *build_value(char *data) {
    struct Value *v = malloc(sizeof(struct Value));
    v->data = data;
    return v;
}

struct Pair *build_pair(char *key, struct Value *v) {
    struct Pair *p = malloc(sizeof(struct Pair));
    p->id = fnv1a(key);
    p->key = key;
    p->value = v;

    return p;
}

struct Hashmap *build_hashmap(size_t size) {
    struct Hashmap *h = malloc(sizeof(struct Hashmap));
    h->size = size;
    h->buckets = malloc(size * sizeof(struct Pair));
    for (size_t i = 0; i < size; ++i) {
        h->buckets[i] = NULL;
    }
    return h;
}

void add(struct Hashmap *h, char *value, struct Value *v) {
    struct Pair *p = build_pair(value, v);
    h->buckets[p->id] = p;
}

struct Pair *get(struct Hashmap *h, char *key) {
    unsigned int i = fnv1a(key);
    return h->buckets[i];
}

unsigned int fnv1a(char *string) {
    static unsigned int prime = 16777619;
    unsigned int hash = 2166136261;

    while (*string) {
        hash ^= *string;
        hash *= prime;
        string++;
    }

    return hash % COUNT;
}

int main() {
    printf("NOTE: there may be collisions.\n");
    struct Hashmap *h = build_hashmap(COUNT);

    struct Value *v = build_value("myvalue");
    add(h, "key", v);

    struct Pair *p = get(h, "key");
    if (p != NULL) {
        printf("Value: \"%s\" found!\n", p->value->data);
    } else {
        printf("No value found.\n");
    }

    free(h);
    free(v);
    return 0;
}
