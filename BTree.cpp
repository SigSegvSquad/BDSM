#include "Utility.h"

class BTree {
private:
    typedef struct Node {
        int *keys;
        bool isLeaf;
        int currDegree, minDegree, maxDegree;
        Node **children;
    } Node;

    static Node *createNode(int degree, bool leaf) {
        Node *node = (Node *) malloc(sizeof(Node));
        node->maxDegree = (2 * degree) - 1;
        node->minDegree = degree;
        node->currDegree = 0;
        node->isLeaf = leaf;

        node->keys = (int *) malloc(node->maxDegree * sizeof(int));
        node->children = (Node **) malloc((2 * degree) * sizeof(Node *));
        return node;
    }

    static bool isFull(Node *node) {
        return (node->currDegree < node->maxDegree);
    }

    static void addKey(Node *node){}

    Node *root = nullptr;
    int minDegree;


public:

    Node *search(int key, Node *node) {
        int i;
        for (i = 0; i < node->currDegree && key > node->keys[i]; i++);

        if (node->keys[i] == key) return node;
        else if (node->isLeaf) return nullptr;
        else return search(key, node->children[i]);
    }

    void insert(int key) {
        if (!root) {
            this->root = createNode(this->minDegree, true);
            root->keys[0] = key;
            root->currDegree = 1;
        } else if (isFull(this->root)) {
            Node* node = createNode(this->minDegree, false);

        } else {

        }
    }

    void remove() {

    }

};