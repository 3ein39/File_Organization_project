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

Enrollment::Enrollment(const string& id, int num, const string* crs, const string* grds) {
    studentID = id;
    numCourses = num;
    courses = new string[numCourses];
    grades = new string[numCourses];
    for (int i = 0; i < numCourses; ++i) {
        courses[i] = crs[i];
        grades[i] = grds[i];
    }
}

Enrollment::~Enrollment() {
    delete[] courses;
    delete[] grades;
}

void Enrollment::Pack(VariableLengthRecord& record) const {
    record.Clear();

    record.Pack(0, (void*)studentID.c_str(), studentID.length() + 1);
    for (int i = 0; i < numCourses; ++i) {
        record.Pack(i + 1, (void*)courses[i].c_str(), courses[i].length() + 1);
        record.Pack(i + numCourses + 1, (void*)grades[i].c_str(), grades[i].length() + 1);
    }
}

void Enrollment::Unpack(VariableLengthRecord& record) {
    char buffer[100];
    record.Unpack(0, buffer);
    studentID = buffer;

    for (int i = 0; i < numCourses; ++i) {
        record.Unpack(i + 1, buffer);
        courses[i] = buffer;

        record.Unpack(i + numCourses + 1, buffer);
        grades[i] = buffer;
    }
}

void Enrollment::WriteEnrollment(Enrollment& enrollment) {
    fstream file(enrollmentsFile, ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        cout << "Unable to open enrollments file." << endl;
        return;
    }

    VariableLengthRecord record;
    enrollment.Pack(record);
    record.Write(file);

    file.close();
    cout << "Enrollment written successfully!" << endl;
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
        PrintEnrollment(enrollment);
    }

    file.close();
}

void Enrollment::PrintEnrollment(Enrollment& enrollment) {
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

