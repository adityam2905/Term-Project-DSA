#ifndef FILEHANDLER_H
#define FILEHANDLER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "avl.h"  // Assuming AVLTree.h defines the AVL tree and Node structure


using namespace std;


// Utility function to split a string by commas
vector<string> split_by_comma(const string& line);


// Function to process the file and populate the AVL tree
void process_file(const char* filename, AVL& tree);


// Function to handle initial database of students and courses
void handle_initial_db(AVL& tree, vector<string> lines, vector<Course*> student_courses);


// Functions for different operations on the AVL tree
void handle_roll_greater_than(AVL &tree, string line);
void handle_roll_less_than(AVL &tree, string line);
void handle_roll_between(AVL &tree, string line);
void handle_CGPA_greater_than(AVL &tree, string line);
void handle_CGPA_lesser_than(AVL &tree, string line);
void handle_CGPA_between_than(AVL &tree, string line);
void handle_modify_student(AVL &tree, string line);
void handle_delete_student(AVL &tree, string line);
void handle_add_course(AVL &tree, string line);
void handle_modify_course(AVL& tree, string line);
void handle_delete_course(AVL &tree, string line);


// Functions to print student data based on specific conditions
void printGreaterThan(Node* root, int roll_no);
void printLesserThan(Node* root, int roll_no);
void print_roll_between(Node* root, int n1, int n2);
void print_student_greater_cgpa(Node* root, float cgpa);
void print_student_lesser_cgpa(Node* root, float cgpa);
void print_student_between_cgpa(Node* root, float cgpa_low, float cgpa_high);
void inOrderTraversal(Node*root);
#endif // FILEHANDLER_H

