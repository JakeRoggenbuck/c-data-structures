#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Copyright (c) 2023 Jake Roggenbuck
 *
 * Inspired by a blog post: https://jr0.org/posts/bloom-filters/
 */

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct BloomFilter {
    size_t size;
    bool *boolarr;
};

struct BloomFilter build_bloom_filter(size_t size) {
    struct BloomFilter b;
    b.size = size;
    b.boolarr = calloc(size, sizeof(bool));

    return b;
}

void resize(struct BloomFilter *b, size_t new_size) {
    int old_size = b->size;
    b->size = new_size;
    b->boolarr = realloc(b->boolarr, new_size * sizeof(bool));

    for (int i = old_size; i < b->size; ++i) {
        b->boolarr[i] = 0;
    }
}

int hash_1(char *word);
int hash_2(char *word);
int hash_3(char *word);

void set(struct BloomFilter *b, size_t index) { b->boolarr[index] = 1; }
void unset(struct BloomFilter *b, size_t index) { b->boolarr[index] = 0; }
bool get(struct BloomFilter *b, size_t index) { return b->boolarr[index]; }

void add(struct BloomFilter *b, char *value) {
    int on = hash_1(value) % b->size;
    int tw = hash_2(value) % b->size;
    int th = hash_3(value) % b->size;

    // Set all of the bools in the indexes to 1 to "register" the word
    set(b, on);
    set(b, tw);
    set(b, th);
}

bool check(struct BloomFilter *b, char *value) {
    int on = hash_1(value) % b->size;
    int tw = hash_2(value) % b->size;
    int th = hash_3(value) % b->size;

    // If all of the bools are 1, then it's likely that this word has been added
    if (get(b, on) && get(b, tw) && get(b, th)) {
        return true;
    }

    return false;
}

int hash_1(char *word) {
    // Credit: sdbm
    int h = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        h = word[i] + (h << 6) + (h << 16) - h;
    }
    return h;
}

int hash_2(char *word) {
    // Credit: djb2
    int h = 5381;
    for (int i = 0; word[i] != '\0'; i++) {
        h = ((h << 5) + h) + word[i];
    }
    return h;
}

int hash_3(char *word) {
    // Credit: djb2 - modified
    int h = 11;
    for (int i = 0; word[i] != '\0'; i++) {
        h = ((h << 3) + h) + word[i];
    }
    return h;
}

void debug_bloom_filter(struct BloomFilter *b) {
    printf("[ ");
    for (int i = 0; i < MIN(10, b->size); ++i) {
        printf("%d ", b->boolarr[i] ? 1 : 0);
    }

    if (b->size > 10) {
        printf(" ... ");

        for (int i = b->size - 10; i < b->size; ++i) {
            printf(" %d", b->boolarr[i] ? 1 : 0);
        }
    }

    printf(" ] size: %zu\n", b->size);
}

void demo() {
    struct BloomFilter b = build_bloom_filter(4);

    set(&b, 0);
    set(&b, 1);
    set(&b, 3);

    debug_bloom_filter(&b);

    resize(&b, 6);

    debug_bloom_filter(&b);
}

int main() {
    struct BloomFilter b = build_bloom_filter(2000);
    add(&b, "hello");

    if (check(&b, "hello")) {
        printf("'hello' is found!\n");
    }

    if (check(&b, "helloo")) {
        printf("'helloo' is found!\n");
    } else {
        printf("'helloo' not found :(\n");
    }

    add(&b, "Jake");

    if (check(&b, "Jake")) {
        printf("'Jake' is found!\n");
    } else {
        printf("'Jake' not found :(\n");
    }

    if (check(&b, "jake")) {
        printf("'jake' is found!\n");
    } else {
        printf("'jake' not found :(\n");
    }

    return 0;
}
