#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

struct Node build_node(int val) {
    struct Node n;
    n.val = val;
    n.right = NULL;
    n.left = NULL;
    return n;
}

void display(struct Node *base) {
    printf("%d ", base->val);

    if (base->right != NULL) {
        display(base->right);
    }

    if (base->left != NULL) {
        display(base->left);
    }
}

int main() {
    struct Node base = build_node(1);

    struct Node r = build_node(2);
    struct Node l = build_node(3);

    base.left = &l;
    base.right = &r;

    display(&base);
}
