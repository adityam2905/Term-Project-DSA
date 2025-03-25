#include "filehandler.h"
using namespace std;

vector<string> split_by_comma(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

void process_file(const char* filename, AVL& tree) {   // Changed AVL parameter to reference
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line == "# 1") {  // Start of student data section
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                vector<string> lines;

                // Extract the number of courses from the line
                int num_courses = stoi(split_by_comma(line)[3]);
                vector<Course*> student_courses;

                // Add the student info line to the lines vector
                lines.push_back(line);

                // Now, read the courses for this student
                for (int i = 0; i < num_courses; i++) {
                    getline(file, line);

                    // Split the course data by comma
                    vector<string> course_data = split_by_comma(line);

                    // Create a Course object and add it to the student_courses vector
                    Course *c = new Course(stoi(course_data[0]), stoi(course_data[1]));  // Both parameters are int
                    student_courses.push_back(c);
                }

                // Insert the student along with their courses into the AVL tree
                handle_initial_db(tree, lines, student_courses);
            }
            tree.printTree();
        } else if (line == "# 7") { // Example command block for roll greater than
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_roll_greater_than(tree, line);
            }
            tree.printTree();
        } else if (line == "# 8") { // Roll less than
            while(getline(file, line) && !line.empty() && line[0] != '#') {
                handle_roll_less_than(tree, line);
            }
            tree.printTree();
        } else if (line == "# 9") { // Roll between
            while(getline(file, line) && !line.empty() && line[0] != '#') {
                handle_roll_between(tree, line);
            }
            tree.printTree();
        } else if (line == "# 10") { // CGPA greater than
            while(getline(file, line) && !line.empty() && line[0] != '#') {
                handle_CGPA_greater_than(tree, line);
            }
            tree.printTree();
        } else if (line == "# 11") { // CGPA lesser than
            while(getline(file, line) && !line.empty() && line[0] != '#') {
                handle_CGPA_lesser_than(tree, line);
            }
            tree.printTree();
        } else if (line == "# 12") { // CGPA between
            while(getline(file, line) && !line.empty() && line[0] != '#') {
                handle_CGPA_between_than(tree, line);
            }
            tree.printTree();
        } else if (line == "# 2") { // Modify student
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_modify_student(tree, line);
            }
            tree.printTree();
        } else if (line == "# 6") { // Delete student
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_delete_student(tree, line);
            }
            tree.printTree();
        } else if (line == "# 3") { // Add course
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_add_course(tree, line);
            }
            tree.printTree();
        } else if (line == "# 4") { // Modify course
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_modify_course(tree, line);
            }
            tree.printTree();
        } else if (line == "# 5") { // Delete course
            while (getline(file, line) && !line.empty() && line[0] != '#') {
                handle_delete_course(tree, line);
            }
            tree.printTree();
        }
    }
    file.close();
}




void handle_initial_db(AVL& tree, vector<string> lines, vector<Course*> student_courses) {
    // Parsing the student data
    vector<string> header = split_by_comma(lines[0]);
    int roll_no = stoi(header[0]);  // Extract the roll number
    string name = header[1];  // Extract the name
    float cgpa = stof(header[2]);  // Extract the CGPA
    int num_courses = stoi(header[3]);  // Extract the number of courses

    // Insert the student into the AVL tree
    tree.root= tree.insert(tree.root,roll_no, name, cgpa, num_courses, student_courses);
}

void  handle_roll_greater_than( AVL &tree, string line) {
   
    int roll_no = stoi(line);
    Node* root = tree.root;
    printGreaterThan( tree.root, roll_no);
    
}
void printGreaterThan(Node* root, int roll_no){
    if (root == nullptr)
        return;
    
    // Traverse the left subtree first
    if (root->value > roll_no) {
        // Print the current node if its value is greater than the given value
        cout << root->value << " ";
    }

    // If the value is greater, it is possible that the left subtree has greater values too
    if (root->value > roll_no) {
        printGreaterThan(root->left, roll_no);
    }

    // Always traverse the right subtree since it can contain larger values
    if (root->value > roll_no) {
        printGreaterThan(root->right, roll_no);
    }
}

void handle_roll_less_than(AVL &tree , string line) {
    
    int roll_no = stoi (line);
    Node* root = tree.root;
    printLesserThan( tree.root, roll_no);
}
void printLesserThan(Node* root, int roll_no) {
    if (root == nullptr)
        return;

    // Traverse the left subtree first
    printLesserThan(root->left, roll_no);

    // Print the node if its value is less than the given roll_no
    if (root->value < roll_no) {
        cout << root->value << " ";
    }

    // Traverse the right subtree
    printLesserThan(root->right, roll_no);
}


void handle_roll_between(AVL &tree, string line){
    
    int n1 = stoi(split_by_comma(line)[0]); // Convert the first part to an integer
    int n2 = stoi(split_by_comma(line)[1]); // Convert the second part to an integer
    Node* root = tree.root;
    print_roll_between(tree.root,n1,n2);
}
void print_roll_between(Node* root, int n1, int n2) {
    if (root == nullptr)
        return;

    // Traverse the left subtree if the current node's value is greater than n1
    if (root->value > n1) {
        print_roll_between(root->left, n1, n2);
    }

    // Print the current node if its value is between n1 and n2 (inclusive)
    if (root->value >= n1 && root->value <= n2) {
        cout << root->value << " ";
    }

    // Traverse the right subtree if the current node's value is less than n2
    if (root->value < n2) {
        print_roll_between(root->right, n1, n2);
    }
}


void handle_CGPA_greater_than(AVL &tree , string line) {
    vector<string> data = split_by_comma(line);
    float cgpa = stof (data[0]);
    Node* root= tree.root;
    print_student_greater_cgpa(tree.root,cgpa);
}
void print_student_greater_cgpa(Node* root, float cgpa) {
    if (root == nullptr) return;

    // Traverse the left subtree first if the current node's cgpa is greater than threshold
    if (root->cgpa > cgpa) {
        print_student_greater_cgpa(root->left, cgpa);
    }

    // Print the current node's cgpa if it's greater than the threshold
    if (root->cgpa > cgpa) {
        cout << root->cgpa << " ";
    }

    // Traverse the right subtree if the current node's cgpa is greater than threshold
    if (root->cgpa > cgpa) {
        print_student_greater_cgpa(root->right, cgpa);
    }
}

void handle_CGPA_lesser_than(AVL &tree , string line) {
    vector<string> data = split_by_comma(line);
    float cgpa = stof (data[0]);
    Node* root= tree.root;
    print_student_lesser_cgpa(tree.root,cgpa);
}
void print_student_lesser_cgpa(Node* root, float cgpa) {
    if (root == nullptr) return;

    // Traverse the left subtree if the current node's cgpa is less than threshold
    if (root->cgpa < cgpa) {
        print_student_lesser_cgpa(root->left, cgpa);
    }

    // Print the current node's cgpa if it's less than the threshold
    if (root->cgpa < cgpa) {
        cout << root->cgpa << " ";
    }

    // Traverse the right subtree if the current node's cgpa is less than threshold
    if (root->cgpa < cgpa) {
        print_student_lesser_cgpa(root->right, cgpa);
    }
}

void handle_CGPA_between_than(AVL &tree , string line) {
    vector<string> data = split_by_comma(line);
    float cgpaf = stof (data[0]);
    float cgpal = stof (data[1]);
    Node* root= tree.root;
    print_student_between_cgpa(tree.root,cgpaf,cgpal);
}
void print_student_between_cgpa(Node* root, float cgpa_low, float cgpa_high) {
    if (root == nullptr) return;

    // Traverse the left subtree if the current node's cgpa is greater than the lower bound
    if (root->cgpa > cgpa_low) {
        print_student_between_cgpa(root->left, cgpa_low, cgpa_high);
    }

    // Print the current node's cgpa if it's within the range
    if (root->cgpa >= cgpa_low && root->cgpa <= cgpa_high) {
        cout << root->cgpa << " ";
    }

    // Traverse the right subtree if the current node's cgpa is less than the upper bound
    if (root->cgpa < cgpa_high) {
        print_student_between_cgpa(root->right, cgpa_low, cgpa_high);
    }
}

void handle_modify_student(AVL &tree, string line){
    vector<string> tokens = split_by_comma(line);
    int roll = stoi(tokens[0]);
    float newcg = stof(tokens[1]);
    Node* root = tree.root;
    Node* to_modify = tree.findNodeByRollNumber(root, roll);
    to_modify->cgpa = newcg;
}

void handle_delete_student(AVL &tree, string line) {
    vector<string> tokens = split_by_comma(line);
    int roll = stoi(tokens[0]);
    float newcg = stof(tokens[1]);
    Node* root = tree.root;
    tree.deleteNode(root,roll);
}

void handle_add_course(AVL &tree, string line) {
    vector<string> data = split_by_comma(line);
    int roll_no = stoi(data[0]);
    Course *c = new Course(stoi(data[1]), stoi(data[2]));
    Node* root = tree.root;
    Node* to_modity =tree.findNodeByRollNumber(root,roll_no);
    to_modity->courses.push_back(c);
}

void handle_modify_course(AVL &tree, string line) {
    vector<string> data = split_by_comma(line);
    int roll_no = stoi(data[0]);
    int code_to=stoi(data[1]);
    int marks_to_keep= stof(data[2]);
    Node* root = tree.root;
    Node* to_modity =tree.findNodeByRollNumber(root,roll_no);
    for(auto i: to_modity->courses){
        if(i->courseCode==code_to){
            i->marks = marks_to_keep;
        }
    }
}

void handle_delete_course(AVL &tree, string line) {
    vector<string> data = split_by_comma(line);
    int roll_no = stoi(data[0]);
    int course_id = stoi(data[1]);
    Node* root = tree.root;
    Node* to_modity =tree.findNodeByRollNumber(root,roll_no);
    int i=0;
    for(i;i<to_modity->numSubjects;i++){
        if(to_modity->courses[i]->courseCode==course_id)break;
    }
    to_modity->courses.erase(to_modity->courses.begin()+i);

    
}
