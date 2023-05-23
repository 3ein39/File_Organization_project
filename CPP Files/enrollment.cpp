//
// Created by hussein on 5/22/23.
//
#include "enrollment.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const string enrollmentsFile = "enrollments.dat";

Enrollment::Enrollment() {
    numCourses = 0;
    courses = nullptr;
    grades = nullptr;
}

//Enrollment::Enrollment(const string& id, int num, const string* crs, const string* grds) {
//    studentID = id;
//    numCourses = num;
//    courses = new string[numCourses];
//    grades = new string[numCourses];
//    for (int i = 0; i < numCourses; ++i) {
//        courses[i] = crs[i];
//        grades[i] = grds[i];
//    }
//}
//
//Enrollment::~Enrollment() {
//    delete[] courses;
//    delete[] grades;
//}

int Enrollment::Pack(VariableLengthRecord& record) const {

    int result, recordSize = 0;
    // id | numCourses
    recordSize = 2 + 2;
    for (int i = 0; i < numCourses; ++i) {
        recordSize += courses[i].size() + 1;
        recordSize += grades[i].size() + 1;
    }

    record.Clear(recordSize);

    result = record.Pack(0, (void*)&studentID, sizeof(studentID));
    result = record.Pack(1, (void*)&numCourses, sizeof(numCourses));
    for (int i = 2; i < numCourses + 1; ++i) {
        result = result && record.Pack(i + 1, (void*)courses[i].c_str(), courses[i].length() + 1);
        result = result && record.Pack(i + numCourses + 1, (void*)grades[i].c_str(), grades[i].length() + 1);
    }
    return result;
}

int Enrollment::Unpack(VariableLengthRecord& record) {
    int result;
    result = result && record.Unpack(0, (char*)&studentID);
    result = result && record.Unpack(1, (char*)&numCourses);
    for (int i = 2; i < numCourses + 2; ++i) {
        result = result && record.Unpack(i, (char*)courses[i - 2].c_str());
        result = result && record.Unpack(i, (char*)grades[i - 2].c_str());
    }
    return result;
}

void Enrollment::WriteEnrollment(VariableLengthRecord& record) {
//    fstream file(enrollmentsFile, ios::in | ios::out | ios::binary | ios::app);
//    if (!file) {
//        cout << "Unable to open enrollments file." << endl;
//        return;
//    }

    Enrollment enrollment = *this;

    record.init(enrollment.numCourses * 2 + 2); // Assuming each course has a corresponding grade
    record.AddField(0, 'D', '|');
    record.AddField(1, 'D', '|');
    for (int i = 2; i < enrollment.numCourses + 2; ++i) {
        record.AddField(i, 'D', '|'); // Field for course
        record.AddField(i + enrollment.numCourses, 'D', '|'); // Field for grade
    }

//    enrollment.Pack(record);
//    record.Write(file);

//    file.close();
//    cout << "Enrollment written successfully!" << endl;
}


void Enrollment::ReadEnrollments() {
    ifstream file(enrollmentsFile, ios::binary);
    if (!file) {
        cout << "Unable to open enrollments file." << endl;
        return;
    }

    VariableLengthRecord record;
    while (record.Read(file)) {
        Enrollment enrollment;
        enrollment.Unpack(record);
        enrollment.PrintEnrollment();
    }

    file.close();
}

void Enrollment::PrintEnrollment() {
    Enrollment enrollment = *this;
    cout << "Student ID: " << enrollment.studentID << endl;
    cout << "Courses: ";
    for (int i = 0; i < enrollment.numCourses; ++i) {
        cout << enrollment.courses[i] << " ";
    }
    cout << endl;
    cout << "Grades: ";
    for (int i = 0; i < enrollment.numCourses; ++i) {
        cout << enrollment.grades[i] << " ";
    }
    cout << endl;
}

