#include "B+ Tree/BPlusTree.h"
#include "B Tree/BTree.h"
#include "Database/Student.h"
#include "Utility.h"

int main() {
    BPlusTree bPlusTree;
    StudentDatabase studentDatabase;
    studentDatabase.readInputBPlusTree(&bPlusTree);

    studentDatabase.printStudent(bPlusTree.search(3));

    return 0;
}

//int main()
//{
//    BPlusTree node;
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
//    node.search(16);
//
//    return 0;
//}