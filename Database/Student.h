#ifndef BDSM_STUDENT_H
#define BDSM_STUDENT_H

#include "../Utility.h"
#include "../B Tree/BTree.h"
#include "../B+ Tree/BPlusTree.h"



class StudentDatabase {
private:
    vector<Student*> studentData;
public:
    bool readInputBTree(BTree *index);
    bool readInputBPlusTree(BPlusTree *index);

    static void printStudent(Student *student);
    static Student *createStudentEntry(int rn, string fn, string ln, string g, int m);
};


#endif //BDSM_STUDENT_H
