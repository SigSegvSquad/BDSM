#include "BTree.h"

BTree::BTree(int t) {
    root = nullptr;
    this->t = t;
}

void BTree::traverse() {
    if (root != nullptr) root->traverse();
}

BNode *BTree::search(int k) {
    return (this->root == nullptr) ? nullptr : this->root->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {

            auto *s = new BNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        } else
            root->insertNonFull(k);
    }
}

void BTree::remove(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }
    root->remove(k);
    if (root->n == 0) {
        BNode *tmp = root;
        if (root->isLeaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }
}


