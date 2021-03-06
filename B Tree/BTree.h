#ifndef BDSM_BTREE_H
#define BDSM_BTREE_H

#include "BNode.h"
#include "../Utility.h"


class BTree {
private:
    BNode *root; 
    int t;

public:
    explicit BTree(int _t);

    Student *search(int k) ;

    void insert(Student* student);
    void remove(int k);
    void traverse();
};

#endif //BDSM_BTREE_H
