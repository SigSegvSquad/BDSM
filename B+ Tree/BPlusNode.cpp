#include "BPlusNode.h"

// Constructor of Node
BPlusNode::BPlusNode()
{
    //key = new int[MAX];
    student = new Student*[MAX];
    ptr = new BPlusNode*[MAX + 1];
}