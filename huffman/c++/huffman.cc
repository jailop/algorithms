#include <cstdlib>
#include <cstring>
#include <cstdint>  // char
#include <iostream>
#include <memory>

using namespace std;

const int array_size = 256;

struct Node {
    char symb;
    int freq;
    Node *left;
    Node *right;

    Node(char symb, int freq) 
        : symb(symb), freq(freq), left(nullptr), right(nullptr) {
    }
    
    Node(Node *nd) // Just copy the content, not thep pointers
        : symb(nd->symb), freq(nd->freq), left(nullptr), right(nullptr) {

        }
    
    Node(Node& a, Node& b) {
        symb = 0;
        freq = a.freq + b.freq;
        if (a.freq > b.freq) {
            left = &a; right = &b;
        } else if (a.freq < b.freq) {
            left = &b; right = &a;
        } else if (a.symb < b.symb) {  // They have the same frequency
            left = &a;  right = &b;    // So, order by symbol
        } else {
            left = &b;
            right = &a;
        }
    }
};

struct Queue;

struct Tree {
    Node *root;
    
    Tree(Queue q);

    Tree(string s) : root(nullptr) {
        const int n = array_size;
        int freqs[n];
        for (int i = 0; i < n; i++)
            freqs[i] = 0;
        for (size_t i = 0; i < s.size(); i++) {
            // cout << s[i] << ' ' << int(s[i]) << endl;
            freqs[int(s[i])]++;
        }
        for (int i = 0; i < n; i++)
            if (freqs[i] > 0) {
                // cout << char(i) << ' ' << i << endl;
                insert(new Node(char(i), freqs[i]));
            }
    }

    ~Tree() {
        free(root); 
    }

    void free(Node *nd) {
        if (!nd)
            return;
        if (nd->left) free(nd->left);
        if (nd->right) free(nd->right);
        delete nd;
    }

    void insert(Node *nd) {
        Node *curr = root;
        if (!root) {
            root = nd;
            return;
        }
        for (bool inserted = false; !inserted; ) {
            if (nd->freq < curr->freq) {
                if (!curr->left) {
                    curr->left = nd;
                    inserted = true;
                } else
                    curr = curr->left;
            } else {
                if (!curr->right) {
                    curr->right = nd;
                    inserted = true;
                } else
                    curr= curr->right;
            }
        }
    }
};

struct Queue {
    int size;
    Node *queue[array_size];

    Queue(Tree *t) : size(0) {
        extract(t->root);
    }

    void extract(Node *nd) {
        if (nd->left)
            extract(nd->left);
        queue[size++] = nd;
        if (nd->right)
            extract(nd->right);
    }
};

Tree::Tree(Queue q) : root(nullptr) {
    Node *a, *b, *c;
    for (int i = 0; i < q.size; ) {
        a = new Node(q.queue[i++]);
        if (i== q.size) {
            if (root) 
                root = new Node(*a, *root); 
            else
                root = a;
            break;
        }
        b = new Node(q.queue[i++]);
        c = new Node(*a, *b);
        if (root)
            root = new Node(*c, *root);
        else
            root = c;
    }
}

void huff_code(Node *nd, string s) {
    if (nd->left)
        huff_code(nd->left, s + '0');
    if (!nd->left && !nd->right)
        cout << nd->symb << ' ' << nd->freq << ' ' << s << endl;
    if (nd->right)
        huff_code(nd->right, s + '1');
}

void huffman(string s) {
    Tree t(s);
    Queue q(&t);
    Tree h(q);
    huff_code(h.root, "");
}

int main() {
    string s = "ACCEBFFFFAAXXBLKE";
    huffman(s);
    return 0;
}
