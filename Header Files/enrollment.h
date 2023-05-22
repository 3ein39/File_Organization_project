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
    std::string* courses;
    std::string* grades;
    short numCourses;

    Enrollment();
//    Enrollment(const std::string& id, int num, const std::string* crs, const std::string* grds);
    ~Enrollment();

    int Pack(VariableLengthRecord& record) const;
    int Unpack(VariableLengthRecord& record) ;

    void WriteEnrollment( VariableLengthRecord& record);
    static void ReadEnrollments();
    void PrintEnrollment();

};

#endif  // ENROLLMENT_H
