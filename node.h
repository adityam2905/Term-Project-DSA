// node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "course.h"  // Assuming Course is defined in course.h

class Node {
public:
    int value;
    float cgpa;
    int numSubjects;
    std::string name;
    char courseID;

    Node* left;
    Node* right;
    int height;
    std::vector<Course*> courses;  // Now storing pointers to Course

    // Constructor to initialize a Node
    Node(int value, const std::string& name, float cgpa, int numSubjects, const std::vector<Course*>& courses);
    ~Node();  // Destructor to delete Course pointers
};

#endif // NODE_H
