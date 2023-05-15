#include "student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int studentCount = 0;
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
    ofstream TestOut("deltext.dat", ios::out | ios::binary);
    if (initial)
         outRecord.WriteHeader(TestOut), initial = false;  // Only Once.
    outRecord.Write(TestOut);
    ++studentCount;
    student.Print(cout);
}

void MngStdPerInfo();

void ShowAllData() {
    VariableLengthRecord inRecord;
    ifstream TestIn("deltext.dat", ios::in | ios::binary);

    while (inRecord.Read(TestIn)) {
        Student student;

        // Unpack the student data
        student.Unpack(inRecord);

        // Display the student details
        cout << "ID: " << student.id << endl;
        cout << "Name: " << student.Name << endl;
        cout << "GPA: " << student.gpa << endl;
        cout << "Grade: " << student.grade << endl;
        cout << endl;
    }

    TestIn.close();
}
//void ShowAllData() {
//    Student student;
//    VariableLengthRecord outRecord, inRecord;
//#pragma region Reading (UnPacking)
//
//    ifstream TestIn ("deltext.dat", ios::in | ios::binary);
//
//    while(inRecord.Read(TestIn)) {
//        inRecord.ReadHeader(TestIn);
////        cout <<"read "<<inRecord.Read(TestIn)<<endl;
//        cout <<"unpack "<<student.Unpack(inRecord)<<endl;
//        student.Print(cout);
//
//    }
//    TestIn.close();
//#pragma endregion
//
//}

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

void MngStdPerInfo() {
    system("clear");
    int s;
    cout << "1-Add New Student" << endl << endl;
    cout << "-1 Back" << endl;
    cout << "0- Exit" << endl;
    cin >> s;
    switch (s) {
        case 1:system("clear"); AddNewStudent();
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