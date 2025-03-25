#ifndef AVL_H
#define AVL_H


#include "node.h"
#include <iostream>
#include <algorithm>  // for std::max


class AVL {
public:
   Node* root;


   AVL() : root(nullptr) {}


   Node* insert(Node* root, int key, const std::string& name, float cgpa, int numCourses, const std::vector<Course*>& courses);
   void insert_course(Node* root, int courseCode, float marks);  // To add a course
   void inorder(Node* root);


   // Utility methods for balancing the tree
   int getheight(Node* root);
   int getbalance(Node* root);
   Node* rightrotate(Node* root);
   Node* leftrotate(Node* root);
   Node* findNodeByRollNumber(Node* root, int roll_no);
   Node* deleteNode(Node* &root, int roll_no);
   Node* minValueNode(Node* node);


   // New function to print the entire tree
   void printTree();
};


#endif // AVL_H

