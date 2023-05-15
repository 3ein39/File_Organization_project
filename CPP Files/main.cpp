#include "student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
	Student student;

	VariableLengthRecord outRecord, inRecord;

	student.id = 120;
	strcpy(student.Name, "Ames");
    student.gpa = 3.6;
    student.grade = 2;

	student.InitRecord(outRecord);

	cout << "pack student " << student.Pack(outRecord) << endl;


	#pragma region Writing (Packing)



	ofstream TestOut("deltext.dat", ios::out | ios::binary);

	outRecord.WriteHeader(TestOut);  // Only Once.
	
	outRecord.Write(TestOut);
	student.Print(cout);

	student.id = 130;
	strcpy(student.Name, "Ahmed");
    student.gpa = 2;
    student.grade = 1;
	
	student.Pack(outRecord);  // Precord  => array  of  char   120Ames| , 130Ahmed|

	outRecord.Write(TestOut);

	student.Print(cout);

	TestOut.close();

	#pragma endregion

	#pragma region Reading (UnPacking)


	ifstream TestIn ("deltext.dat", ios::in | ios::binary);
	inRecord.ReadHeader(TestIn);
	
	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<student.Unpack(inRecord)<<endl;
	student.Print(cout);


	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<student.Unpack(inRecord)<<endl;
	student.Print(cout);
	#pragma endregion

}