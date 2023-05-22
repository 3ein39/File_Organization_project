## Project Description

The project is a simple file-based system for managing student records in C++. The system stores student records in a file using a variable-length record approach with a `|` delimiter. Each record is stored on a separate line with the fields separated by the `|` character in the following order:

> Id|Name|Grade|Gpa|


where:

- `Id` is an integer representing the student's ID
- `Name` is a string representing the student's name
- `Grade` is an integer representing the student's grade
- `Gpa` is a float representing the student's grade point average.

The project provides several operations for managing student records, including adding a new record, updating an existing record, deleting a record, and searching for records by ID or name.

## Student Information

The `Student` class contains the following fields:

- `Id`: An integer representing the student's ID.
- `Name`: A string representing the student's name.
- `Grade`: An integer representing the student's grade.
- `Gpa`: A float representing the student's grade point average.


### Course Enrollments

Each enrollment record represents a student's enrollment in multiple courses. Each enrollment consists of the following fields:

> StudentId|Course1|Grade1|Course2|Grade2|...|CourseN|GradeN|


- `StudentId` is an integer representing the student's ID.
- `numCourses` is an integer representing the student's enrolled courses count.
- `Course1`, `Course2`, ..., `CourseN` are strings representing the names of the courses.
- `Grade1`, `Grade2`, ..., `GradeN` are strings representing the grades achieved in each course.

The number of courses can vary for each enrollment.

## Class Description

The `VariableLengthRecord` class provides methods for packing and unpacking records into binary format. The size of each record is determined by the length of each field and the `|` delimiter.

Overall, this project provides a simple and efficient file organization system for managing student records using a variable-length record approach.
