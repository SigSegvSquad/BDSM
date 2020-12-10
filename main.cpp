#include "B+ Tree/BPlusTree.h"
#include "B Tree/BTree.h"
#include "Database/Student.h"
#include "Utility.h"

int main() {
    BTree bTree(4);
    StudentDatabase studentDatabase;
    studentDatabase.readInputBTree(&bTree);

    studentDatabase.printStudent(bTree.search(49));
    return 0;
}