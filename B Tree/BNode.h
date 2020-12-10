#ifndef BDSM_BNODE_H
#define BDSM_BNODE_H

#include "../Utility.h"


class BNode {
private:
    int *keys;
    int n, t;
    BNode **children;
    bool isLeaf;

public:

    BNode(int _t, bool _leaf);

    BNode *search(int k);
    int findKey(int k);

    void traverse();

    void insertNonFull(int k);

    void splitChild(int i, BNode *y);

    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);

    int getPredecessor(int idx);
    int getSuccessor(int idx);

    void merge(int idx);
    void fill(int idx);

    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);

    friend class BTree;
};

#endif //BDSM_BNODE_H
