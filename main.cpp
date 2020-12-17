#include "B+ Tree/BPlusTree.h"
#include "B Tree/BTree.h"
#include "Database/Student.h"
#include "Utility.h"

int main() {
    BPlusTree bPlusTree;
    BTree bTree(4);
    StudentDatabase studentDatabase;
    studentDatabase.readInputBPlusTree(&bPlusTree);

    studentDatabase.printStudent(bPlusTree.search(71));

    return 0;
}


//int main()
//{
//    BPTree node;
//
//    // Create B+ Tree
//    node.insert(6);
//    node.insert(16);
//    node.insert(26);
//    node.insert(36);
//    node.insert(46);
//
//    // Function Call to search node
//    // with value 16
//    node.search(46);
//
//    return 0;
//}