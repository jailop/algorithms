#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define height(node) (node ? node->height : 0)
#define balance(node) (node ? height(node->left) - height(node->right) : 0);

typedef struct Node {
    int value;
    int height;
    struct Node *left;
    struct Node *right;
} node_t;

node_t *node_new(int value) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->value = value;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_t *rotate_right(node_t *y) {
    node_t *x = y->left;
    node_t *T2 = y->right;
    x->right = y;
    y->left = T2;
    x->height = max(height(x->left), height(x->right));
    y->height = max(height(y->left), height(y->right));
    return x;
}

node_t *rotate_left(node_t *y) {
    node_t *x = y->right;
    node_t *T2 = y->left;
    x->left = y;
    x->right = T2;
    x->height = max(height(x->left), height(x->right));
    y->height = max(height(y->left), height(y->right));
    return x;
}

node_t *rebalance(node_t *node, int value) {
    int bal = 0;
    node->height = 1 + max(height(node->left), height(node->right));
    bal = balance(node);
    if (bal > 1 && value < node->left->value)
        return rotate_right(node);
    if (bal < -1 && value > node->right->value)
        return rotate_left(node);
    if (bal > 1 && value > node->left->value) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (bal < -1 && value < node->right->value) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

node_t *node_insert(node_t *node, int value) {
    if (!node) return node_new(value);
    if (value < node->value)
        node->left = node_insert(node->left, value);
    else if (value > node->value)
        node->right = node_insert(node->right, value);
    else
        return node;
    return rebalance(node, value);
}

node_t *node_min_value(node_t *node) {
    node_t *curr = node;
    while (curr->left)
        curr = curr->left;
    return curr;
}

node_t *node_delete(node_t *node, int value) {
    /* empty tree */
    if (!node) return NULL;
    /* recursive calls while value is different from node's value */
    if (value < node->value)
        node->left = node_delete(node->left, value);
    else if (value > node->value)
        node->right = node_delete(node->right, value);
    else {
        /* one or both of the sides are empty */
        if (!node->left || !node->right) {
            node_t *temp = !node->left ? node->right : NULL;
            if (!temp) {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;
            free(temp);
        }
        else {
            node_t *temp = node_min_value(node->right);
            node->value = temp->value;
            node->right = node_delete(node->right, temp->value);
        }
    }
    if (!node)
        return NULL;
    return rebalance(node, value);
}

void node_print(node_t *node, int root) {
    if (node) {
        node_print(node->left, 0);
        printf("%d ", node->value);
        node_print(node->right, 0);
    }
    if (root) printf("\n");
}

int main() {
    node_t *root = NULL;
    node_print(root, 1);
    root = node_insert(root, 22);
    node_print(root, 1);
    root = node_insert(root, 14);
    node_print(root, 1);
    root = node_insert(root, 72);
    node_print(root, 1);
    root = node_insert(root, 44);
    node_print(root, 1);
    root = node_delete(root, 22);
    node_print(root, 1);
    root = node_delete(root, 72);
    node_print(root, 1);
    root = node_delete(root, 15);
    node_print(root, 1);
    return 0;
}
