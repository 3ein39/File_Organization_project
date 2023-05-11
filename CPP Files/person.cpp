#include <string.h>
#include "person.h"

Person::Person()
{
	id = 0;
	Name[0] = 0;
}

Person::Person(short shId, char name[])
{
	id = shId;
	strcpy_s(Name, name);
}

// initialize a VariableLengthRecord to be used for Persons
void Person::InitRecord(VariableLengthRecord& record)
{
	record.init(2);
	record.AddField(0, 'F', 2);  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'D', '|');

}

int Person::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7

	recordSize = 2 + strlen(Name) + 1;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short));
	
	result = result && record.Pack(1, (void*)Name, strlen(Name));

	return result;
}

int Person::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, (char*)&id);
	result = result && record.Unpack(1, Name, true);
	return result;
}

void Person::Print(ostream& stream)
{
	stream << "Person:"
		<< "\tId '" << id << "'\n"
		<< "\tName '" << Name << "'\n";
}
