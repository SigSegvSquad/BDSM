#include "BNode.h"

BNode::BNode(int t1, bool leaf1) {
    t = t1;
    isLeaf = leaf1;
    keys = new int[2 * t - 1];
    studentIndex = new Student *[2 * t - 1];
    children = new BNode *[2 * t];
    n = 0;
}

int BNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void BNode::remove(int k) {
    int idx = findKey(k);

    if (idx < n && keys[idx] == k) {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (isLeaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = (idx == n);
        if (children[idx]->n < t)
            fill(idx);
        if (flag && idx > n)
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

void BNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
        studentIndex[i - 1] = studentIndex[i];
    }
    n--;
}

void BNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->n >= t) {
        Student *pred = getPredecessor(idx);
        keys[idx] = pred->rollNum;
        studentIndex[idx] = pred;
        children[idx]->remove(pred->rollNum);
    } else if (children[idx + 1]->n >= t) {
        Student *succ = getSuccessor(idx);
        keys[idx] = succ->rollNum;
        studentIndex[idx] = succ;
        children[idx + 1]->remove(succ->rollNum);
    } else {
        merge(idx);
        children[idx]->remove(k);
    }
}

Student * BNode::getPredecessor(int idx) {
    BNode *cur = children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->n];
    return cur->studentIndex[cur->n - 1];
}

Student * BNode::getSuccessor(int idx) {

    BNode *cur = children[idx + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];

    return cur->studentIndex[0];
}

void BNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->n >= t)
        borrowFromPrev(idx);

    else if (idx != n && children[idx + 1]->n >= t)
        borrowFromNext(idx);

    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BNode::borrowFromPrev(int idx) {

    BNode *child = children[idx];
    BNode *sibling = children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
        child->studentIndex[i + 1] = child->studentIndex[i];
    }

    if (!child->isLeaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = keys[idx - 1];
    child->studentIndex[0] = studentIndex[idx - 1];

    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];
    studentIndex[idx - 1] = sibling->studentIndex[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void BNode::borrowFromNext(int idx) {

    BNode *child = children[idx];
    BNode *sibling = children[idx + 1];

    child->keys[(child->n)] = keys[idx];
    child->studentIndex[(child->n)] = studentIndex[idx];

    if (!(child->isLeaf))
        child->children[(child->n) + 1] = sibling->children[0];

    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
    studentIndex[idx] = sibling->studentIndex[0];

    for (int i = 1; i < sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
        sibling->studentIndex[i - 1] = sibling->studentIndex[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void BNode::merge(int idx) {
    BNode *child = children[idx];
    BNode *sibling = children[idx + 1];

    child->keys[t - 1] = keys[idx];
    child->studentIndex[t - 1] = studentIndex[idx];

    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
        child->studentIndex[i + t] = sibling->studentIndex[i];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + t] = sibling->children[i];
    }

    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
        studentIndex[i - 1] = studentIndex[i];
    }

    for (int i = idx + 2; i <= n; ++i)
        children[i - 1] = children[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
}

void BNode::insertNonFull(Student *student) {
    int k = student->rollNum;

    int i = n - 1;

    if (isLeaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            studentIndex[i + 1] = studentIndex[i];
            i--;
        }
        keys[i + 1] = k;
        studentIndex[i + 1] = student;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        children[i + 1]->insertNonFull(student);
    }
}

void BNode::splitChild(int i, BNode *y) {

    auto *z = new BNode(y->t, y->isLeaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
        z->studentIndex[j] = y->studentIndex[j + t];
    }

    if (!y->isLeaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
        studentIndex[j + 1] = studentIndex[j];
    }

    keys[i] = y->keys[t - 1];
    studentIndex[i] = y->studentIndex[t - 1];

    n++;
}

void BNode::traverse() {

    int i;
    for (i = 0; i < n; i++) {
        if (!isLeaf)
            children[i]->traverse();
        cout << " " << keys[i];
    }

    if (!isLeaf)
        children[i]->traverse();
}

Student *BNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;

    if (keys[i] == k) return studentIndex[i];
    if (isLeaf) return nullptr;
    return children[i]->search(k);
}
