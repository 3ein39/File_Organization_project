#include <iostream>
//#include "fixtext.h"
//#include "lentext.h"
#include "varlen.h"

using namespace std;

class Person
{
public:
	// fields
	short	id;
	char	Name[11];

	//operations
	Person();
	Person(short shId, char name[]);

	void InitRecord(VariableLengthRecord&); //set Record  Configuration
	
	int Pack(VariableLengthRecord&);	//  From ObjectPerson  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Person  => Read

	
	void Print(ostream&);

};