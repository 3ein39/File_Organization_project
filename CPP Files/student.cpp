#include <string.h>
#include "student.h"

Student::Student()
{
	id = 0;
	Name[0] = 0;
    grade = 0;
    gpa = 0;
//
//    subjects[0] = "Computer Science";
//    subjects[1] = "File Organization";
//    subjects[2] = "DSP";
}

Student::Student(short id, char name[], float gpa,/* int degrees[], */ int grade)
{
	this->id = id;
	strcpy(Name, name);
    this->gpa = gpa;
    this->grade = grade;

//    for (int i = 0; i < 3; ++i) {
//        this->degrees[i] = degrees[i];
//    }
}

// initialize a VariableLengthRecord to be used for Student
void Student::InitRecord(VariableLengthRecord& record)
{
	record.init(10);
	record.AddField(0, 'D', '|');
    record.AddField(1, 'D', '|');
    record.AddField(2, 'D', '|');
    record.AddField(3, 'D', '|');
//    record.AddField(4, 'D', '|');
//    record.AddField(5, 'D', '|');
//    record.AddField(6, 'D', '|');
//    record.AddField(7, 'D', '|');
//    record.AddField(8, 'D', '|');
//    record.AddField(9, 'D', '|');
}
int Student::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7
    // id -- name -- del -- grade -- gpa
	recordSize = 2 + strlen(Name) + 1 + 4 + 4;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short));
    cout <<"id after pack" << id << endl;
	
	result = result && record.Pack(1, (void*)Name, strlen(Name));

    result = result && record.Pack(2, (void*)&gpa, sizeof(gpa));

    result = result && record.Pack(3, (void*)&grade, sizeof(grade));

//    result = result && record.Pack(4, (void*)&subjects[0], subjects[0].size() * 8);
//
//    result = result && record.Pack(5, (void*)&degrees[0], sizeof(degrees[0]));
//
//    result = result && record.Pack(6, (void*)&subjects[1], subjects[1].size() * 8);
//
//    result = result && record.Pack(7, (void*)&degrees[1], sizeof(degrees[1]));
//
//    result = result && record.Pack(8, (void*)&subjects[2], subjects[2].size() * 8);
//
//    result = result && record.Pack(9, (void*)&degrees[2], sizeof(degrees[2]));
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
	stream << "Student:"
		<< "\tId '" << id << "'\n"
		<< "\tName '" << Name << "'\n"
        << "\tGpa '" << gpa << "'\n"
        << "\tGrade '" << grade << "'\n";
}
