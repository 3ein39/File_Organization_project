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
    recordSize = 2 + (3 * 4);
    for (int i = 0; i < 3; ++i) {
        recordSize += courses[i].size() + 1;
    }

    record.Clear(recordSize);

    result = record.Pack(0, (void*)&studentID, sizeof(studentID));
    result = result && record.Pack(1, (void*)courses[0].c_str(), courses[0].size());
    result = result && record.Pack(2, (void*)&grades[0], courses[0].size());
    result = result && record.Pack(3, (void*)courses[1].c_str(), courses[1].size());
    result = result && record.Pack(4, (void*)&grades[1], courses[1].size());
    result = result && record.Pack(5, (void*)courses[2].c_str(), courses[2].size());
    result = result && record.Pack(6, (void*)&grades[2], courses[2].size());
    return result;
}

int Enrollment::Unpack(VariableLengthRecord& record) {
    int result = true;
    result = result && record.Unpack(0, (char*)&studentID);

    char temporary[255];
    for (int i = 0; i < 3; ++i)
    {
        result = result && record.Unpack(i + 1, (char *)temporary, true);
        courses[i] = temporary;

        int gradeValue; // To store the grades with refrence
        result = result && record.Unpack(i + 4, (char*)&gradeValue);
        grades[i] = gradeValue;
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

    record.init(7); // Assuming each course has a corresponding grade
    record.AddField(0, 'D', '|');
    record.AddField(1, 'D', '|');
    record.AddField(2, 'D', '|');
    record.AddField(3, 'D', '|');
    record.AddField(4, 'D', '|');
    record.AddField(5, 'D', '|');
    record.AddField(6, 'D', '|');

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

void Enrollment::PrintEnrollment()
{
    Enrollment enrollment = *this;
    cout << "Enrollment Information:\n";
    cout << "Student ID: " << enrollment.studentID << endl;
    cout << "Courses:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "\t- " << enrollment.courses[i] << endl;
    }
    cout << "Grades:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "\t- " << enrollment.grades[i] << endl;
    }
    cout << endl;
}

