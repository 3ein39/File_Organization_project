#include "student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

bool initial = true;

void AddNewStudent() {
    Student student;
    VariableLengthRecord outRecord, inRecord;

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
#pragma region Writing (Packing)
    ofstream TestOut("deltext.dat", ios::out | ios::binary | ios::app);
    if (initial)
         outRecord.WriteHeader(TestOut), initial = false;  // Only Once.
    outRecord.Write(TestOut);
    student.Print(cout);

    TestOut.close();
#pragma endregion

}

void MngStdPerInfo();

void ShowAllData();

void STD();

int main()
{
  STD();
//
////
//	student.id = 130;
//	strcpy(student.Name, "Ahmed");
//    student.gpa = 2;
//    student.grade = 1;
////
//	student.Pack(outRecord);  // Precord  => array  of  char   120Ames| , 130Ahmed|
////
//	outRecord.Write(TestOut);
////
//	student.Print(cout);
////
//	TestOut.close();
////
////	#pragma endregion
////
//	#pragma region Reading (UnPacking)


//	ifstream TestIn ("deltext.dat", ios::in | ios::binary);
//	inRecord.ReadHeader(TestIn);

//	cout <<"read "<<inRecord.Read(TestIn)<<endl;
//	cout <<"unpack "<<student.Unpack(inRecord)<<endl;
//	student.Print(cout);
//
//
//	cout <<"read "<<inRecord.Read(TestIn)<<endl;
//	cout <<"unpack "<<student.Unpack(inRecord)<<endl;
//	student.Print(cout);
//	#pragma endregion
//
}

void updateStudentInfo();

void MngStdPerInfo() {
    system("clear");
    int s;
    cout << "1-Add New Student" << endl;
    cout << "2-Update Student Info" << endl;
    cout << "-1 Back" << endl;
    cout << "0- Exit" << endl;
    cin >> s;
    switch (s) {
        case 1:system("clear"); AddNewStudent();
            break;
        case 2: updateStudentInfo();
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
    cout << "3-Show all student Data" << endl;
    //    cout << "4-Find student by ID" << endl << endl;
    //    cout << "For exit press 0\n";
    cin >> s;
    switch (s) {
    case 1:system("clear"); MngStdPerInfo();
        break;
        //        case 2:controle();
    //            break;
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
        cout << student.id << endl;
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

            cout << "id before" << student.id << endl;
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



void ShowAllData() {
    Student student;
    VariableLengthRecord outRecord, inRecord;
#pragma region Reading (UnPacking)

    ifstream TestIn ("deltext.dat", ios::in | ios::binary);
    inRecord.ReadHeader(TestIn);

    while(inRecord.Read(TestIn)) {
//        cout <<"read "<<inRecord.Read(TestIn)<<endl;
        cout <<"unpack "<<student.Unpack(inRecord)<<endl;
        student.Print(cout);

    }
    TestIn.close();
#pragma endregion

}