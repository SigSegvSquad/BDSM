#ifndef BDSM_BPLUSTREE_H
#define BDSM_BPLUSTREE_H

#include "BPlusNode.h"
#include "../Utility.h"

class BPlusTree {
    BPlusNode* root;
    void insertInternal(Student *,
                        BPlusNode*,
                        BPlusNode*);
    BPlusNode* findParent(BPlusNode*, BPlusNode*);

public:
    BPlusTree();
    Student* search(int);
    void insert(Student *);
    BPlusNode* getRoot();
};


#endif //BDSM_BPLUSTREE_H
