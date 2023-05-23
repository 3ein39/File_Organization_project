#include <string.h>
#include "student.h"

Student::Student()
{
	id = 0;
	Name[0] = 0;
    grade = 0;
    gpa = 0;
}

Student::Student(short id, char name[], float gpa,/* int degrees[], */ int grade)
{
	this->id = id;
	strcpy(Name, name);
    this->gpa = gpa;
    this->grade = grade;

}

void Student::InitRecord(VariableLengthRecord& record)
{
	record.init(10);
	record.AddField(0, 'D', '|');
    record.AddField(1, 'D', '|');
    record.AddField(2, 'D', '|');
    record.AddField(3, 'D', '|');
}
int Student::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7
    // id -- name -- del -- grade -- gpa
	recordSize = 2 + strlen(Name) + 1 + 4 + 4;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short));

	result = result && record.Pack(1, (void*)Name, strlen(Name));

    result = result && record.Pack(2, (void*)&gpa, sizeof(gpa));

    result = result && record.Pack(3, (void*)&grade, sizeof(grade));

	return result;
}

int Student::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, (char*)&id);
	result = result && record.Unpack(1, Name, true);
    result = result && record.Unpack(2, (char*)&gpa);
    result = result && record.Unpack(3, (char*)&grade);
	return result;
}

void Student::Print(ostream& stream)
{
    stream << "Student Information:\n"
           << "\tID: " << id << "\n"
           << "\tName: " << Name << "\n"
           << "\tGPA: " << gpa << "\n"
           << "\tGrade: " << grade << "\n";
}

