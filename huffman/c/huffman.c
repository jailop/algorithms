#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

/** node_t is type for varables
 *  containing symbols and their frequency
 */
typedef struct node {
    struct node *left, *right;
    unsigned freq;
    char symbol;
} node_t;

typedef struct {
    node_t *root;
    unsigned size;
} tree_t;

typedef struct {
    node_t **data;
    unsigned size;
} queue_t;

/** node_new creates a new node
 *  @param[in] symbol
 *  @param[in] frequency
 *  @param[out] The new node. It must be deleted with node_free
 */
node_t *node_new(char symbol, unsigned freq) {
    node_t *nd = (node_t*) malloc(sizeof(node_t));
    nd->symbol = symbol;
    nd->freq = freq;
    nd->left = nd->right = NULL;
    return nd;
}

void node_link(node_t *nd, node_t *a, node_t *b) {
    if (a->freq > b->freq) {
        nd->left = a; nd->right = b;
    } else if (a->freq < b->freq) {
        nd->left = b; nd->right = a;
    } else if (a->symbol < b->symbol) {
        nd->left = a; nd->right = b;
    } else {
        nd->left = b; nd->right = a;
    }
}

tree_t *tree_new() {
    tree_t *t = (tree_t*) malloc(sizeof(tree_t));
    t->root = NULL;
    t->size = 0;
    return t;
}

void tree_insert(tree_t *tree, char symbol, unsigned freq) {
    node_t *curr = NULL;
    node_t *prev = tree->root;
    node_t *nd = node_new(symbol, freq);
    tree->size++;
    if (tree->root == NULL) {
        tree->root = nd;
        return;
    }
    while(1) {
        if (prev->freq > nd->freq) {
            curr = prev->left;
            if (!curr) {
                prev->left = nd;
                break;
            }
        }
        else {
            curr = prev->right;
            if (!curr) {
                prev->right = nd;
                break;
            }
        }
        prev = curr;
    }
}

void queue_extract(queue_t *queue, node_t *node) {
    if (node->left)
        queue_extract(queue, node->left);
    queue->data[queue->size++] = node;
    if (node->right)
        queue_extract(queue, node->right);
}

queue_t *queue_from_tree(tree_t *t) {
    queue_t *q = (queue_t*) malloc(sizeof(queue_t));
    q->size = 0;
    q->data = (node_t**) malloc(sizeof(node_t*) * t->size);
    queue_extract(q, t->root);
    return q;
}

tree_t *tree_from_string(char *s) {
    unsigned i;
    int len = 256;
    tree_t *t = tree_new();
    unsigned *freqs = (unsigned*) malloc(sizeof(unsigned) * len);
    for (i = 0; i < len; i++)
        freqs[i] = 0;
    for (i = 0; s[i] != 0; i++)
        freqs[(int) s[i]]++;
    for (i = 0; i < len; i++)
        if (freqs[i] > 0)
            tree_insert(t, i, freqs[i]);
    free(freqs);
    return t;
}

void node_free(node_t *node) {
    if (node->left)
        node_free(node->left);
    if (node->right)
        node_free(node->right);
    free(node);
}

void tree_free(tree_t *t) {
    node_free(t->root);
    free(t);
}

void queue_free(queue_t *q) {
    free(q->data);
    free(q);
}

tree_t *tree_huffman(queue_t *q) {
    unsigned i;
    tree_t *t = tree_new();
    for (i = 0; i < q->size; i++) {
        node_t *a = node_new(q->data[i]->symbol, q->data[i]->freq);
        i++;
        if (i == q->size && t->root) {
            node_t *b = node_new(0, a->freq + t->root->freq); 
            node_link(b, a, t->root);
            t->root = b;
            break;
        }
        else {
            node_t *b = node_new(q->data[i]->symbol, q->data[i]->freq);
            node_t *c = node_new(0, a->freq + b->freq);      
            node_link(c, a, b);
            if (i < q->size && t->root) {
                node_t *d = node_new(0, c->freq + t->root->freq);        
                node_link(d, c, t->root);
                t->root = d;
            }
            else 
                t->root = c;
        }
    }
    return t;
}

void huffman_node(node_t *nd, char *sa, unsigned len, char code) {
    unsigned step = len + 1;
    char *sb = (char*) 
        malloc(sizeof(char) * BUFSIZE);
    sb[0] = 0;
    if (sa) {
        strcpy(sb, sa);
        sb[len] = code;
        sb[len + 1] = 0;
    }
    else {
        step = 0;
    }
    if (nd->left)
        huffman_node(nd->left, sb, step, '0');
    if (nd->symbol != 0) {
        printf("%c %d %s\n", nd->symbol, nd->freq, sb);
    }
    if (nd->right)
        huffman_node(nd->right, sb, step, '1');
    free(sb);
}

#define huffman_from_tree(t) huffman_node((t)->root, NULL, 0, '0')

void huffman(char *s) {
    /* A by frequency sorted tree for symbols */
    tree_t *tree = tree_from_string(s);
    /* The sorted tree is converted into a priority queue*/
    queue_t *queue = queue_from_tree(tree);
    /* A Huffman tree is created */
    tree_t *huff = tree_huffman(queue);
    /* Go by the tree to show codes */
    huffman_from_tree(huff);
    /* Cleaning */
    tree_free(huff);
    queue_free(queue);
    tree_free(tree);
}

char *read_from_stream() {
    char c;
    unsigned i = 0;
    unsigned n = BUFSIZE;
    char *s = (char*) malloc(sizeof(char) * (n + 1));
    while ((c = getchar()) != EOF) {
        s[i++] = c;
        if (i == n) {
            /* More space is needed. Expand the buffer */
            char *t = NULL;
            n *= 2;
            t = (char*) realloc(s, sizeof(char) * (n + 1));
            s = t;
        }
    }
    /* Close the string */
    s[i] = 0;
    return s; 
}

int main() {
    char *s = "ACCEBFFFFAAXXBLKE";
    huffman(s);
    return 0;
}
