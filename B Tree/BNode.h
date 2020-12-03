#ifndef BDSM_BNODE_H
#define BDSM_BNODE_H

#include "../Utility.h"

class BNode {
public:
    key *keys;
    bool isLeaf;
    int currKeys, minKeys, maxKeys;
    BNode **children;

    BNode (int minChildNum, bool leaf);

    bool isFull();

    void traverse();
    BNode* search(key k);
    void insertNonFull(key k);
    void splitChild(int childNum, BNode *y);
};


#endif //BDSM_BNODE_H
