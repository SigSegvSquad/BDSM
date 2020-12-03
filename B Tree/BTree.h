#ifndef BDSM_BTREE_H
#define BDSM_BTREE_H

#include "BNode.h"
#include "../Utility.h"

class BTree {
private:
    BNode *root = nullptr;
    int minKeys;

public:
    BTree(int t);

    BNode *search(key key);

    void insert(key key);
    void traverse();
    void remove();

};

#endif //BDSM_BTREE_H
