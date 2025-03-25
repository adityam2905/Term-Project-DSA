#ifndef COURSE_H
#define COURSE_H

#include <iostream>

class Course {
public:
    int courseCode;
    int marks;

    // Constructor: both parameters are of type int
    Course(int code, int marks);
};

#endif // COURSE_H

