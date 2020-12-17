#include "BPlusTree.h"

BPlusTree::BPlusTree()
{
    root = NULL;
}

// Function to find any element
// in B+ Tree
Student *BPlusTree::search(int x)
{

    // If tree is empty
    if (root == NULL) {
        cout << "Tree is empty\n";
    }

        // Traverse to find the value
    else {

        BPlusNode* cursor = root;

        // Till we reach leaf node
        while (cursor->IS_LEAF == false) {

            for (int i = 0;i < cursor->size; i++) {

                // If the element to be
                // found is not present
                if (x < cursor->student[i]->rollNum) {
                    cursor = cursor->ptr[i];
                    break;
                }

                // If reaches end of the
                // cursor node
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        // Traverse the cursor and find
        // the node with value x
        for (int i = 0;
             i < cursor->size; i++) {

            // If found then return
            if (cursor->student[i]->rollNum == x) {
                cout << "Found\n";
                return cursor->student[i];
            }
        }

        // Else element is not present
        cout << "Not found\n";
    }
}

// Function to implement the Insert
// Operation in B+ Tree
void BPlusTree::insert(Student *student)
{

    // If root is null then return
    // newly created node
    if (root == NULL) {
        root = new BPlusNode;
        root->student[0] = student;
        root->IS_LEAF = true;
        root->size = 1;
    }

        // Traverse the B+ Tree
    else {
        BPlusNode* cursor = root;
        BPlusNode* parent;

        // Till cursor reaches the
        // leaf node
        while (!cursor->IS_LEAF) {

            parent = cursor;

            for (int i = 0;i < cursor->size;i++) {

                // If found the position
                // where we have to insert
                // node
                if (student->rollNum < cursor->student[i]->rollNum) {
                    cursor = cursor->ptr[i];
                    break;
                }

                // If reaches the end
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size < MAX) {
            int i = 0;
            while (i < cursor->size && student->rollNum > cursor->student[i]->rollNum) {
                i++;
            }

            for (int j = cursor->size;j > i; j--) {
                cursor->student[j] = cursor->student[j - 1];
            }

            cursor->student[i] = student;
            cursor->size++;

            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }

        else {

            // Create a newLeaf node
            BPlusNode* newLeaf = new BPlusNode;

            Student *virtualNode[MAX + 1];

            // Update cursor to virtual
            // node created
            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->student[i];
            }
            int i = 0, j;

            // Traverse to find where the new
            // node is to be inserted
            while (i < MAX && student->rollNum > virtualNode[i]->rollNum) {
                i++;
            }

            // Update the current virtual
            // Node to its previous
            for (int j = MAX + 1;j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }

            virtualNode[i] = student;
            newLeaf->IS_LEAF = true;

            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;

            cursor->ptr[cursor->size] = newLeaf;

            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];

            cursor->ptr[MAX] = NULL;

            // Update the current virtual
            // Node's key to its previous
            for (i = 0; i < cursor->size; i++) {
                cursor->student[i] = virtualNode[i];
            }

            // Update the newLeaf key to
            // virtual Node
            for (i = 0, j = cursor->size;
                 i < newLeaf->size;
                 i++, j++) {
                newLeaf->student[i] = virtualNode[j];
            }

            // If cursor is the root node
            if (cursor == root) {

                // Create a new Node
                BPlusNode* newRoot = new BPlusNode;

                // Update rest field of
                // B+ Tree Node
                newRoot->student[0] = newLeaf->student[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {

                // Recursive Call for
                // insert in internal
                insertInternal(newLeaf->student[0],parent,newLeaf);
            }
        }
    }
}

// Function to implement the Insert
// Internal Operation in B+ Tree
void BPlusTree::insertInternal(Student *student,
                               BPlusNode* cursor,
                               BPlusNode* child)
{

    // If we doesn't have overflow
    if (cursor->size < MAX) {
        int i = 0;

        // Traverse the child node
        // for current cursor node
        while (i < cursor->size && student->rollNum > cursor->student[i]->rollNum) {
            i++;
        }

        // Traverse the cursor node
        // and update the current key
        // to its previous node key
        for (int j = cursor->size;j > i; j--) {
            cursor->student[j] = cursor->student[j - 1];
        }

        // Traverse the cursor node
        // and update the current ptr
        // to its previous node ptr
        for (int j = cursor->size + 1;j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }

        cursor->student[i] = student;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }

        // For overflow, break the node
    else {

        // For new Interval
        BPlusNode* newInternal = new BPlusNode;
        Student *virtualKey[MAX + 1];
        BPlusNode* virtualPtr[MAX + 2];

        // Insert the current list key
        // of cursor node to virtualKey
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->student[i];
        }

        // Insert the current list ptr
        // of cursor node to virtualPtr
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;

        // Traverse to find where the new
        // node is to be inserted
        while (i < MAX && student->rollNum > virtualKey[i]->rollNum) {
            i++;
        }

        // Traverse the virtualKey node
        // and update the current key
        // to its previous node key
        for (int j = MAX + 1;j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }

        virtualKey[i] = student;

        // Traverse the virtualKey node
        // and update the current ptr
        // to its previous node ptr
        for (int j = MAX + 2;j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }

        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;

        cursor->size = (MAX + 1) / 2;

        newInternal->size = MAX - (MAX + 1) / 2;

        // Insert new node as an
        // internal node
        for (i = 0, j = cursor->size + 1;i < newInternal->size;i++, j++) {
            newInternal->student[i] = virtualKey[j];
        }

        for (i = 0, j = cursor->size + 1;i < newInternal->size + 1;i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }

        // If cursor is the root node
        if (cursor == root) {
            // Create a new root node
            BPlusNode* newRoot = new BPlusNode;

            // Update key value
            newRoot->student[0] = cursor->student[cursor->size];
            // Update rest field of
            // B+ Tree Node
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }

        else {

            // Recursive Call to insert
            // the data
            insertInternal(cursor->student[cursor->size],findParent(root,cursor),newInternal);
        }
    }
}

// Function to find the parent node
BPlusNode* BPlusTree::findParent(BPlusNode* cursor,BPlusNode* child)
{
    BPlusNode* parent;

    // If cursor reaches the end of Tree
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }

    // Traverse the current node with
    // all its child
    for (int i = 0;i < cursor->size + 1; i++) {
        // Update the parent for the
        // child Node
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }

            // Else recursively traverse to
            // find child node
        else {
            parent = findParent(cursor->ptr[i],child);

            // If parent is found, then
            // return that parent node
            if (parent != NULL)
                return parent;
        }
    }

    // Return parent node
    return parent;
}

// Function to get the root Node
BPlusNode* BPlusTree::getRoot()
{
    return root;
}

