#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define COUNT UINT_MAX

struct Pair {
    size_t id;
    char *key;
    char *value;
};

struct Hashmap {
    struct Pair **buckets;
};

struct Hashmap *build_hashmap(int size) {
    struct Hashmap *h = malloc(sizeof(struct Hashmap));
    h->buckets = malloc(size * sizeof(struct Pair *));
    for (int i = 0; i < size; ++i) {
        h->buckets[i] = NULL;
    }
    return h;
}

unsigned int fnv1a(char *string) {
    static unsigned int prime = 16777619;
    unsigned int hash = 2166136261;

    while (*string) {
        hash ^= *string;
        hash *= prime;
        string++;
    }

    return hash;
}

int main() {
    struct Hashmap *h = build_hashmap(COUNT);
    return 0;
}
