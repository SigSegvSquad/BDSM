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
