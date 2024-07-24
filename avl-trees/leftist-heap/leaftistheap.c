
typedef struct lh_node {
    int key;
    int dist;
    struct lh_node *left;
    struct lh_node *right;
} lh_node_t;



lh_node_t *lh_merge(lh_node_t *h1, lh_node_t *h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    if (h1->key < h2->key)
        return lh_merge_2(h1, h2);
    else
        return lh_merge_2(h1, h2);
}

