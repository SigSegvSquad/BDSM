#ifndef BDSM_NODE_H
#define BDSM_NODE_H


#include "../Utility.h"

#define MAX 3

// BP node
class BPlusNode {
public:
    bool isLeaf;
    int *key, size;
    BPlusNode** ptr;
    Student **studentIndex;
    friend class BPlusTree;
    BPlusNode();
};


#endif //BDSM_NODE_H
