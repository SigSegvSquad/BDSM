#include "BPlusTree.h"


#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


BPlusTree::BPlusTree() {
    root = NULL;
}


Student *BPlusTree::search(int x) {


    if (root == NULL) {
        cout << "Tree is empty\n";
    } else {

        BPlusNode *cursor = root;


        while (!cursor->IS_LEAF) {

            for (int i = 0; i < cursor->size; i++) {


                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }


                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }


        for (int i = 0; i < cursor->size; i++) {


            if (cursor->key[i] == x) {
                cout << "Found\n";
                return cursor->studentIndex[i];
            }
        }


        cout << "Not found\n";
    }
}


void BPlusTree::insert(Student *student) {
    int x = student->rollNum;


    if (root == NULL) {
        root = new BPlusNode;
        root->key[0] = x;
        root->studentIndex[0] = student;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        BPlusNode *cursor = root;
        BPlusNode *parent;


        while (!cursor->IS_LEAF) {

            parent = cursor;

            for (int i = 0;i < cursor->size;i++) {


                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }


                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size) {
                i++;
            }

            for (int j = cursor->size;
                 j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
                cursor->studentIndex[j] = cursor->studentIndex[j - 1];
            }

            cursor->key[i] = x;
            cursor->studentIndex[i] = student;
            cursor->size++;

            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else {


            BPlusNode *newLeaf = new BPlusNode;

            int virtualNode[MAX + 1];
            Student *virtualStudent[MAX + 1];


            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
                virtualStudent[i] = cursor->studentIndex[i];
            }
            int i = 0, j;


            while (x > virtualNode[i]
                   && i < MAX) {
                i++;
            }


            for (int j = MAX + 1;
                 j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
                virtualStudent[j] = virtualStudent[j - 1];
            }

            virtualNode[i] = x;
            virtualStudent[i] = student;

            newLeaf->IS_LEAF = true;

            cursor->size = (MAX + 1) / 2;
            newLeaf->size
                    = MAX + 1 - (MAX + 1) / 2;

            cursor->ptr[cursor->size]
                    = newLeaf;

            newLeaf->ptr[newLeaf->size]
                    = cursor->ptr[MAX];

            cursor->ptr[MAX] = NULL;


            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
                cursor->studentIndex[i] = virtualStudent[i];
            }


            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
                newLeaf->studentIndex[i] = virtualStudent[j];
            }


            if (cursor == root) {


                BPlusNode *newRoot = new BPlusNode;


                newRoot->key[0] = newLeaf->key[0];
                newRoot->studentIndex[0] = newLeaf->studentIndex[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {


                insertInternal(newLeaf->studentIndex[0],
                               parent,
                               newLeaf);
            }
        }
    }
}


void BPlusTree::insertInternal(Student *student,
                               BPlusNode *cursor,
                               BPlusNode *child) {
    int x = student->rollNum;

    if (cursor->size < MAX) {
        int i = 0;


        while (x > cursor->key[i]
               && i < cursor->size) {
            i++;
        }


        for (int j = cursor->size;
             j > i; j--) {

            cursor->key[j] = cursor->key[j - 1];
            cursor->studentIndex[j] = cursor->studentIndex[j - 1];
        }


        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }

        cursor->key[i] = x;
        cursor->studentIndex[i] = student;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {


        BPlusNode *newInternal = new BPlusNode;
        int virtualKey[MAX + 1];
        Student *virtualStudent[MAX + 1];
        BPlusNode *virtualPtr[MAX + 2];


        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
            virtualStudent[i] = cursor->studentIndex[i];
        }


        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;


        while (x > virtualKey[i] && i < MAX) {
            i++;
        }


        for (int j = MAX + 1; j > i; j--) {

            virtualKey[j] = virtualKey[j - 1];
            virtualStudent[j] = virtualStudent[j - 1];
        }

        virtualKey[i] = x;
        virtualStudent[i] = student;


        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }

        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;

        cursor->size = (MAX + 1) / 2;

        newInternal->size = MAX - (MAX + 1) / 2;


        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {

            newInternal->key[i] = virtualKey[j];
            newInternal->studentIndex[i] = virtualStudent[j];
        }

        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }


        if (cursor == root) {


            BPlusNode *newRoot = new BPlusNode;


            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->studentIndex[0] = cursor->studentIndex[cursor->size];


            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {


            insertInternal(cursor->studentIndex[cursor->size],
                           findParent(root,
                                      cursor),
                           newInternal);
        }
    }
}


BPlusNode *BPlusTree::findParent(BPlusNode *cursor,
                                 BPlusNode *child) {
    BPlusNode *parent;


    if (cursor->IS_LEAF
        || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }


    for (int i = 0;
         i < cursor->size + 1; i++) {


        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent
                    = findParent(cursor->ptr[i],
                                 child);


            if (parent != NULL)
                return parent;
        }
    }


    return parent;
}


BPlusNode *BPlusTree::getRoot() {
    return root;
}

