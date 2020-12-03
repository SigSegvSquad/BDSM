#include "BTree.h"

BTree::BTree(int minKeys) {
    this->minKeys = minKeys;
}

void BTree::insert(key k) {
    if (!root) {
        root = new BNode(minKeys, true);
        root->keys[0] = k;
        root->currKeys = 1;
    } else {
        if (root->currKeys = 2*(minKeys) - 1) {
            BNode *newRoot = new BNode(minKeys, false);
            newRoot->children[0] = root;
            newRoot->splitChild(0, root);

            int i = 0;
            if (newRoot->keys[0] < k) i++;
            newRoot->children[i]->insertNonFull(k);
            root = newRoot;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTree::traverse() {
    if (root) root->traverse();
}

BNode *BTree::search(key key) {
    if (root) root->search(key);
}

void BTree::remove() {
}
