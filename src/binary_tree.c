#include <stdio.h>
#include <stdlib.h>

/* Copyright (c) 2023 Jake Roggenbuck
 *
 * Binary tree implementation
 */

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

struct Node *build_node(int val) {
    struct Node *n = malloc(sizeof(struct Node));
    n->val = val;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void display(struct Node *base, int level, int is_left) {
    if (base == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        if (i == level - 1) {
            printf(is_left ? "L: " : "R: ");
        } else {
            printf("  ");
        }
    }

    printf("%d\n", base->val);

    display(base->left, level + 1, 1);
    display(base->right, level + 1, 0);
}

void insert(struct Node *base, int val) {
    if (val < base->val) {
        if (base->left == NULL) {
            base->left = build_node(val);
        } else {
            insert(base->left, val);
        }
    }

    if (val > base->val) {
        if (base->right == NULL) {
            base->right = build_node(val);
        } else {
            insert(base->right, val);
        }
    }
}

int main() {
    struct Node *base = build_node(8);

    struct Node *l = build_node(4);
    struct Node *r = build_node(12);

    base->left = l;
    base->right = r;

    insert(base, 16);
    insert(base, 6);
    insert(base, 2);

    display(base, 0, 0);
}
