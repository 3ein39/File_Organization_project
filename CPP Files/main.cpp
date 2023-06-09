#include "student.h"
#include "enrollment.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


bool initial = true;
bool initial2 = true;
void AddNewStudent();
void updateMenu();
void MngStdPerInfo();
void findStdByID();
void ShowAllData();
void STD();
void deleteStudent();
void updateStudentInfo();
void showDeletedData();
void ShowGrades(int id);
void updateStudentDegrees();
void deleteDegree(int id);
int main() {
    STD();
}
void deleteStudent() {
    int searchID;
    cout << "Enter the ID of the student to delete: ";
    cin >> searchID;

    fstream file("deltext.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Unable to open the file." << endl;
        return;
    }

    VariableLengthRecord record;
    Student student;

    bool found = false;
    record.ReadHeader(file);
    while (record.Read(file)) {
        // Unpack the record into the student object
        student.Unpack(record);
        if (student.id == searchID) {
            file.seekp(-record.RecordSize(), ios::cur);
            short newId = -1;
            file.write((char*)& newId, sizeof(short));


            deleteDegree(student.id);

            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

void deleteDegree(int id) {
    fstream file("enrollments.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Unable to open the file." << endl;
        return;
    }

    VariableLengthRecord record;
    Enrollment enroll;

    bool found = false;
    record.ReadHeader(file);
    while (record.Read(file)) {
        // Unpack the record into the enroll object
        enroll.Unpack(record);
        if (enroll.studentID == id) {
            file.seekp(-record.RecordSize(), ios::cur);
            short newId = 0;
            file.write((char*)& newId, sizeof(short));
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student not found." << endl;
    }
}
void findStdByID() {
    int searchID;
    cout << "Enter the ID of the student: ";
    cin >> searchID;


     Student student;
    VariableLengthRecord outRecord, inRecord;
#pragma region Reading (UnPacking)

    ifstream TestIn ("deltext.dat", ios::in | ios::binary);
    inRecord.ReadHeader(TestIn);

    while(inRecord.Read(TestIn)) {
//        cout <<"read "<<inRecord.Read(TestIn)<<endl;
        bool res = student.Unpack(inRecord);
//        cout <<"unpack "<<student.Unpack(inRecord)<<endl;
        if (student.id == searchID) {
            student.Print(cout);
            ShowGrades(searchID);
        }
    }
    TestIn.close();
#pragma endregion

}
void MngStdPerInfo() {
    system("clear");
    int s;
    cout << "1-Add New Student" << endl;
    cout << "2-Update Student Info" << endl;
    cout << "3-Delete Student" << endl;
    cout << "4-Find Student By ID" << endl;
    cout << "-1 Back" << endl;
    cout << "0- Exit" << endl;
    cin >> s;
    switch (s) {
        case 1:system("clear"); AddNewStudent();
            break;
        case 2: updateMenu();
            break;
        case 3: deleteStudent();
            break;
        case 4: findStdByID();
            break;
        case -1: STD();
            break;
        case 0:exit(0);
        break;
        default: MngStdPerInfo();
    }
    MngStdPerInfo();
}
void STD() {
    system("clear");
    int s;
    cout << "1-Manage Student Personal Information" << endl;
    //    cout << "2-Manage Student Academic Record" << endl;
    cout << "2-Show Deleted Records" << endl;
    cout << "3-Show all student Data" << endl;
    //    cout << "4-Find student by ID" << endl << endl;
    //    cout << "For exit press 0\n";
    cin >> s;
    switch (s) {
    case 1:system("clear"); MngStdPerInfo();
        break;
    case 2: showDeletedData();
        break;
    case 3:ShowAllData();
        break;
    //        case 4: FindStudentById();
    //            break;
    case 0:exit(0);
        break;
    default: STD();
    }
    STD();
}

void updateMenu() {
    system("clear");
    int s;
    cout << "1-Update Student Info" << endl;
    cout << "2-Update Student Degrees" << endl;
    cout << "-1 Back" << endl;
    cout << "0- Exit" << endl;
    cin >> s;
    switch (s) {
        case 1:system("clear"), updateStudentInfo();
            break;
        case 2: updateStudentDegrees();
            break;
        case -1: MngStdPerInfo();
            break;
        case 0:exit(0);
            break;
        default: updateMenu();
    }

}

void updateStudentInfo() {


    int searchID;
    cout << "Enter the ID of the student to update: ";
    cin >> searchID;

    fstream file("deltext.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Unable to open the file." << endl;
        return;
    }

    VariableLengthRecord record;
    Student student;

    bool found = false;
    record.ReadHeader(file);
    while (record.Read(file)) {
        // Unpack the record into the student object
        student.Unpack(record);
        if (student.id == searchID) {
            // Student found, update the information
            cout << "Enter new Name: ";
            cin.ignore();
            cin.getline(student.Name, 11);

            cout << "Enter new GPA: ";
            cin >> student.gpa;

            cout << "Enter new Grade: ";
            cin >> student.grade;

            file.seekp(-record.RecordSize(), ios::cur);
            short newId = -1;
            file.write((char*)& newId, sizeof(short));

            // Pack the updated student data into the record
            file.seekp(0, ios::end);
            student.Pack(record);

            // Write the updated record to the file
            record.Write(file);

            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Student information updated successfully!" << endl;
    } else {
        cout << "Student not found." << endl;
    }
}
void AddNewStudent() {
    Student student;
    VariableLengthRecord outRecord;

    cout << "Enter ID: ";
    cin >> student.id;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(student.Name, 11);

    cout << "Enter GPA: ";
    cin >> student.gpa;

    cout << "Enter Grade: ";
    cin >> student.grade;

    student.InitRecord(outRecord);
    cout << "pack student " << student.Pack(outRecord) << endl;
#pragma region Writing (Packing) for student file
    ofstream TestOut("deltext.dat", ios::out | ios::binary | ios::app);
    if (TestOut.tellp() == 0)
        outRecord.WriteHeader(TestOut), initial = false;  // Only Once.
    outRecord.Write(TestOut);
    student.Print(cout);

    TestOut.close();
#pragma endregion

    Enrollment enroll;
    VariableLengthRecord outRecord2;


    enroll.studentID = student.id;


    for (int i = 0; i < 3; ++i) {
        cout << "Enter Name for " << i + 1 << " course: ";
        cin >> enroll.courses[i];

        cout << "Enter grade for " << i + 1 << " course: ";
        cin >> enroll.grades[i];
    }

    enroll.WriteEnrollment(outRecord2);
    cout << "pack enrollment " << enroll.Pack(outRecord2) << endl;
#pragma region Writing (Packing) for enroll file
    ofstream TestOutt("enrollments.dat", ios::out | ios::binary | ios::app);
    if (TestOutt.tellp() == 0)
        outRecord2.WriteHeader(TestOutt), initial2 = false;  // Only Once.
    outRecord2.Write(TestOutt);
    enroll.PrintEnrollment();

    TestOutt.close();
#pragma endregion

}
void ShowAllData() {
    Student student;
    VariableLengthRecord outRecord, inRecord;
#pragma region Reading (UnPacking)

    ifstream TestIn ("deltext.dat", ios::in | ios::binary);
    inRecord.ReadHeader(TestIn);

    while(inRecord.Read(TestIn)) {
//        cout <<"read "<<inRecord.Read(TestIn)<<endl;
        bool res = student.Unpack(inRecord);
//        cout <<"unpack "<<student.Unpack(inRecord)<<endl;
        if (student.id == -1) continue;
        cout << "unpack " << res << endl;
        student.Print(cout);

        ShowGrades(student.id);
    }
    TestIn.close();
#pragma endregion
}
void showDeletedData() {
        Student student;
    VariableLengthRecord outRecord, inRecord;
#pragma region Reading (UnPacking)

    ifstream TestIn ("deltext.dat", ios::in | ios::binary);
    inRecord.ReadHeader(TestIn);

    while(inRecord.Read(TestIn)) {
//        cout <<"read "<<inRecord.Read(TestIn)<<endl;
        bool res = student.Unpack(inRecord);
//        cout <<"unpack "<<student.Unpack(inRecord)<<endl;
        if (student.id != -1) continue;
        cout << "unpack " << res << endl;
        student.Print(cout);

    }
    TestIn.close();
#pragma endregion

}

void ShowGrades(int id) {
    ifstream file("enrollments.dat", ios::binary);

    if (!file) {
        cout << "Unable to open the file." << endl;
        return;
    }

    VariableLengthRecord record;
    Enrollment enroll;

    record.ReadHeader(file);
    while (record.Read(file)) {
        // Unpack the record into the student object
        enroll.Unpack(record);
        if (enroll.studentID == id)
            enroll.PrintEnrollment();
    }

    file.close();
}
void updateStudentDegrees() {
    int searchID;
    cout << "Enter the ID of the student to update: ";
    cin >> searchID;

    fstream file("enrollments.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Unable to open the file." << endl;
        return;
    }

    VariableLengthRecord record;
    Enrollment enroll;

    bool found = false;
    record.ReadHeader(file);
    while (record.Read(file)) {
        // Unpack the record into the enroll object
        enroll.Unpack(record);
        if (enroll.studentID == searchID) {
            // Student found, update the information

            for (int i = 0; i < 3; ++i) {
                cout << "Enter course name : " << " last : " << enroll.courses[i];
                cin >> enroll.courses[i];

                cout << "Enter course degree : " << " last : " << enroll.grades[i];
                cin >> enroll.grades[i];
            }

            file.seekp(-record.RecordSize(), ios::cur);
            short newId = -1;
            file.write((char*)& newId, sizeof(short));

            // Pack the updated enroll data into the record
            file.seekp(0, ios::end);
            enroll.Pack(record);

            // Write the updated record to the file
            record.Write(file);

            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Student grades updated successfully!" << endl;
    } else {
        cout << "Student not found." << endl;
    }
}
