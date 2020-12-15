#include "BPlusNode.h"

// Constructor of BPlusNode
BPlusNode::BPlusNode()
{
    key = new int[MAX];
    ptr = new BPlusNode*[MAX + 1];
    studentIndex = new Student*[MAX];
}