//
// Created by hussein on 5/22/23.
//
#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include "varlen.h"

class Enrollment {
public:
    short studentID;
    string courses[3];
    int grades[3];

    Enrollment();

    int Pack(VariableLengthRecord& record) const;
    int Unpack(VariableLengthRecord& record) ;

    void WriteEnrollment( VariableLengthRecord& record);
    static void ReadEnrollments();
    void PrintEnrollment();

};

#endif  // ENROLLMENT_H
