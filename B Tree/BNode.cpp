#include "BNode.h"

BNode::BNode(int minKeyNum, bool isLeaf) {
    this->maxKeys = (2 * minKeyNum) - 1;
    this->minKeys = minKeyNum;
    this->currKeys = 0;
    this->isLeaf = isLeaf;

    this->keys = (key *) malloc(this->maxKeys * sizeof(key));
    this->children = (BNode **)
            malloc((2 * minKeyNum) * sizeof(BNode *));
}

bool BNode::isFull() {
    return (this->currKeys == this->maxKeys);
}

void BNode::traverse() {
    int i;
    for (i = 0; i < this->maxKeys; i++) {
        if (!isLeaf)
            children[i]->traverse();
        cout << " " << this->keys[i];
    }

    if (isLeaf == false) children[i]->traverse();
}

BNode *BNode::search(key k) {
    int i;
    for (i = 0; (i < this->maxKeys) && (k > this->keys[i]); i++);

    if (this->keys[i] == k) return this;
    else if (this->isLeaf) return nullptr;
    else return children[i]->search(k);
}

void BNode::insertNonFull(key k) {
    int i = currKeys - 1;
    if (isLeaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        currKeys++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (this->children[i + 1]->isFull()) {
            splitChild(i + 1, this->children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        this->children[i + 1]->insertNonFull(k);
    }
}

void BNode::splitChild(int childNum, BNode *y) {
    BNode *z = new BNode(y->minKeys, y->isLeaf);
    z->currKeys = minKeys - 1;

    for (int j = 0; j < minKeys - 1; j++)
        z->keys[j] = y->keys[j + minKeys];

    if (y->isLeaf == false) {
        for (int j = 0; j < minKeys; j++) {
            z->children[j] = y->children[j + minKeys];
        }
    }

    y->currKeys = minKeys - 1;

    for (int j = currKeys; j >= childNum + 1; j--)
        this->children[j + 1] = this->children[j];

    this->children[childNum + 1] = z;

    for (int j = currKeys - 1; j >= childNum; j--)
        keys[j + 1] = keys[j];

    keys[childNum] = y->keys[minKeys - 1];
    currKeys = currKeys + 1;
}



