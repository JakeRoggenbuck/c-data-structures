#include <stdio.h>
#include <stdlib.h>

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

void display(struct Node *base) {
    printf("%d ", base->val);

    if (base->left != NULL) {
        display(base->left);
    }

    if (base->right != NULL) {
        display(base->right);
    }
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

    display(base);
}
