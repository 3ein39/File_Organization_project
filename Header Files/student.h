#pragma once
#include <iostream>
#include<map>
#include "varlen.h"


using namespace std;

class Student
{
public:
	// fields
	short	id;
	char	Name[11];
    float gpa;
    int grade; // 1 -- 4

	//operations
	Student();
	Student(short shId, char name[], float gpa, /*int degrees[],*/ int grade);

	void InitRecord(VariableLengthRecord&); //set Record  Configuration
	
	int Pack(VariableLengthRecord&);	//  From ObjectPerson  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Person  => Read

	
	void Print(ostream&);

};