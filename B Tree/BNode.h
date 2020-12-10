#ifndef BDSM_BNODE_H
#define BDSM_BNODE_H

#include "../Utility.h"

class BNode {
private:
    int *keys;
    Student **studentIndex;
    int n, t;
    BNode **children;
    bool isLeaf;

public:

    BNode(int _t, bool _leaf);

    Student *search(int k);
    int findKey(int k);

    void traverse();

    void insertNonFull(Student *student);

    void splitChild(int i, BNode *y);

    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);

    Student * getPredecessor(int idx);
    Student * getSuccessor(int idx);

    void merge(int idx);
    void fill(int idx);

    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);

    friend class BTree;
};

#endif //BDSM_BNODE_H
