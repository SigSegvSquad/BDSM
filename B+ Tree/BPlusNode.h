#ifndef BDSM_NODE_H
#define BDSM_NODE_H


#include "../Utility.h"

#define MAX 3

// BP node
class BPlusNode {
    bool IS_LEAF;
    //int *key, size;
    int size;
    Student **student;
    BPlusNode** ptr;
    friend class BPlusTree;

public:
    BPlusNode();
};


#endif //BDSM_NODE_H
