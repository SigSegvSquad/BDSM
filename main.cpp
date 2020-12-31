#include "B+ Tree/BPlusTree.h"
#include "B Tree/BTree.h"
#include "Database/Student.h"
#include "Utility.h"

int main() {
    BPlusTree bPlusTree;
    BTree bTree(4);
    StudentDatabase studentDatabase;
    studentDatabase.readInputBPlusTree(&bPlusTree);

    studentDatabase.printStudent(bPlusTree.search(2));
    studentDatabase.printStudent(bPlusTree.search(11));
    studentDatabase.printStudent(bPlusTree.search(27));
    studentDatabase.printStudent(bPlusTree.search(68));

    return 0;
}

