#include "student.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	Person person;

	VariableLengthRecord outRecord, inRecord;

	person.id = 120;
	strcpy_s(person.Name, "Ames");

	person.InitRecord(outRecord);

	cout << "pack person " << person.Pack(outRecord) << endl;


	#pragma region Writing (Packing)



	ofstream TestOut("deltext.dat", ios::out | ios::binary);

	outRecord.WriteHeader(TestOut);  // Only Once.
	
	outRecord.Write(TestOut);
	person.Print(cout);

	person.id = 130;
	strcpy_s(person.Name, "Ahmed");
	
	person.Pack(outRecord);  // Precord  => array  of  char   120Ames| , 130Ahmed|

	outRecord.Write(TestOut);

	person.Print(cout);

	TestOut.close();

	#pragma endregion

	#pragma region Reading (UnPacking)


	ifstream TestIn ("deltext.dat", ios::in | ios::binary);
	inRecord.ReadHeader(TestIn);
	
	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<person.Unpack(inRecord)<<endl;	
	person.Print(cout);


	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<person.Unpack(inRecord)<<endl;
	person.Print(cout);
	#pragma endregion

}