// node.cpp
#include "node.h"


Node::Node(int value, const std::string& name, float cgpa, int numSubjects, const std::vector<Course*>& courses)
    : value(value), name(name), cgpa(cgpa), numSubjects(numSubjects), left(nullptr), right(nullptr), height(1), courses(courses) {
    // No need to initialize courses here, as it's done in the initializer list
}

Node::~Node() {
    // Cleanup courses if dynamically allocated
    for (auto course : courses) {
        delete course;
    }
}

