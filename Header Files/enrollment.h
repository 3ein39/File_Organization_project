//
// Created by hussein on 5/22/23.
//
#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include "varlen.h"

class Enrollment {
private:
    std::string studentID;
    std::string* courses;
    std::string* grades;
    int numCourses;

public:
    Enrollment();
    Enrollment(const std::string& id, int num, const std::string* crs, const std::string* grds);
    ~Enrollment();

    void Pack(VariableLengthRecord& record) const;
    void Unpack(VariableLengthRecord& record) ;

    static void WriteEnrollment( Enrollment& enrollment);
    static void ReadEnrollments();
    static void PrintEnrollment(Enrollment& enrollment);

};

#endif  // ENROLLMENT_H
