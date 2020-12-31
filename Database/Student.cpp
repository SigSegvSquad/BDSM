#include <sstream>
#include <utility>
#include "Student.h"

void StudentDatabase::printStudent(Student *student) {
    cout << "Roll Number: " << student->rollNum << "\n";
    cout << "First Name:  " << student->firstName << "\n";
    cout << "Last Name:   " << student->lastName << "\n";
    cout << "Gender:      " << student->gender << "\n";
    cout << "Marks:       " << student->marks << "\n\n";
}

Student *StudentDatabase::createStudentEntry(int rn, string fn, string ln, string g, int m) {
    auto *student = new Student;
    student->firstName = std::move(fn);
    student->lastName = std::move(ln);
    student->gender = std::move(g);
    student->marks = m;
    student->rollNum = rn;
    return student;
}


bool StudentDatabase::readInputBTree(BTree *index) {
    ifstream dataFile("../Database/students.csv");
    int count = 0;
    vector<string> row;
    Student* student;
    string line, word, temp;

//    dataFile.open("../students.csv", ios::in);

    while (getline(dataFile, line)) {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        student = createStudentEntry(stoi(row[0]), row[1], row[2], row[3], stoi(row[4]));
        studentData.push_back(student);
        //printStudent(student);
        index->insert(studentData[count]);
        count++;
    }
}

bool StudentDatabase::readInputBPlusTree(BPlusTree *index){
    ifstream dataFile("../Database/students.csv");
    int count = 0;
    vector<string> row;
    Student* student;
    string line, word, temp;

//    dataFile.open("../students.csv", ios::in);

    while (getline(dataFile, line)) {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        student = createStudentEntry(stoi(row[0]), row[1], row[2], row[3], stoi(row[4]));
        studentData.push_back(student);
        //printStudent(student);
        index->insert(studentData[count]);
        count++;
    }
}

