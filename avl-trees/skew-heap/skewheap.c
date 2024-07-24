#include <stdio.h>
#include <stdlib.h>

typedef struct skew_heap {
	int key;
	struct skew_heap *right;
	struct skew_heap *left;
} skew_heap_t;

void swap(void **a, void **b) {
	void **tmp = *a;
	*a = *b;
	*b = tmp;
}

skew_heap_t *skew_heap_new() {
	skew_heap_t *h = (skew_heap_t *) malloc(sizeof(skew_heap_t));
	h->key = 0;
	h->right = NULL;
	h->left = NULL;
	return h;
}

skew_heap_t *skew_heap_merge(skew_heap_t *h1, skew_heap_t *h2) {
	if (!h1) return h2;
	if (!h2) return h1;
	if (h1->key > h2->key) swap((void **) &h1, (void **) &h2);
	swap((void **) &(h1->left), (void **) &(h1->right));
	h1->left = skew_heap_merge(h2, h1->left);
	return h1;
}

void skew_heap_print(skew_heap_t *node, int level) {
	if (!node) return;
	skew_heap_print(node->left, level + 1);
	for (int i = 0; i < level; i++) printf(" ");
	printf("%d\n", node->key);
	skew_heap_print(node->right, level + 1);
}

skew_heap_t *skew_heap_construct(skew_heap_t *root, int heap[], int n) {
	skew_heap_t *tmp;
	for (int i = 0; i < n; i++) {
		tmp = skew_heap_new();
		tmp->key = heap[i];
		root = skew_heap_merge(root, tmp);
	}
	return root;
}

void skew_heap_free(skew_heap_t *node) {
	if (!node) return;
	skew_heap_free(node->left);
	skew_heap_free(node->right);
	free(node);
}

int main() {
	int v1[] = {12, 5, 10};
	int v2[] = {3, 7, 8, 14};
	skew_heap_t *h1 = NULL;
	skew_heap_t *h2 = NULL;
	h1 = skew_heap_construct(h1, v1, 3);
	h2 = skew_heap_construct(h2, v2, 4);
	h1 = skew_heap_merge(h1, h2);
	skew_heap_print(h1, 0);
	skew_heap_free(h1);
	// skew_heap_free(h2);
	return 0;
}
