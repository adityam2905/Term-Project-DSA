 #include "filehandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<std::string> split_by_comma(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

void process_file(const char* filename, node*& root {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "# 1") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                std::vector<std::string> lines;
                
                int num_courses = std::stoi(split_by_comma(line)[3]);

                lines.push_back(line);
                for (int i = 0; i < num_courses; i++) {
                    std::getline(file, line);
                    lines.push_back(line);
                }
                handle_initial_db(root, lines.data());
            }
        } else if (line == "# 7") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_roll_greater_than(root, line);
            }
        } else if (line == "# 8" ) {
             while(std::getline(file,line) && !line.empty() && line[0] != '#' ) {
                 handle_roll_less_than(root, line);
             }
        } else if (line == "# 9" ) {
             while(std::getline(file,line) && !line.empty() && line[0] != '#' ) {
                 handle_roll_between(root, line);
             }
        } else if (line == "# 10" ) {
             while(std::getline(file,line) && !line.empty() && line[0] != '#' ) {
                 handle_CGPA_greater(root, line);
             }
        } else if (line == "# 11" ) {
             while(std::getline(file,line) && !line.empty() && line[0] != '#' ) {
                 handle_CGPA_lesser(root, line);
             }
        } else if (line == "# 12" ) {
             while(std::getline(file,line) && !line.empty() && line[0] != '#' ) {
                 handle_CGPA_between(root, line);
             }
        } 
        
         else if (line == "# 2") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_modify_student(root, line);
            }
        } else if (line == "# 6") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_delete_student(head, line);
            }
        } else if (line == "# 3") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_add_course(root, line);
            }
        } else if (line == "# 4") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_modify_course(head, line);
            }
        } else if (line == "# 5") {
            while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                handle_delete_course(head, line);
            }
        }
    }
    file.close();
}



void handle_initial_db(node*& head, std::string lines[]) {
    std::vector<std::string> header = split_by_comma(lines[0]);
    int roll_no = std::stoi(header[0]);
    float cgpa = std::stof(header[2]);
    int num_courses = std::stoi(header[3]);

    std::vector<CodeMarks> courses // changed once check; 
    for (int = 1; i <= num_courses; i++) {
        std::vector<std::string> course_data = split_by_comma(lines[i]);
        CodeMarks course{std::stoi(course_data[0]), std::stof(course_data[1])};
        courses.push_back(course);
    }
    insert_student(root, roll_no, header[1], cgpa, num_courses, courses);
}

/*  void handle_add_student(Node*& head, std::string line) {
    std::vector<std::string> header = split_by_comma(line);
    int roll_no = std::stoi(header[0]);
    float cgpa = std::stof(header[2]);
    int num_courses = std::stoi(header[3]);

    std::vector<CourseInfo> courses;
    for (size_t i = 4; i < header.size(); i += 2) {
        CourseInfo course{std::stoi(header[i]), std::stof(header[i + 1])};
        courses.push_back(course);
    }
    insert_student(head, roll_no, header[1], cgpa, num_courses, courses);
} */

void handle_modify_student(node*& root, std::string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi(data[0]);
    float new_cgpa = std::stof(data[1]);
    modify_student_cgpa(root, roll_no, new_cgpa);
}

void  handle_roll_greater_than(node* &root, string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi(data[0]);
    print_students_greater_roll(root , roll_no);
}

void handle_roll_less_than(node* &root , string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi (data[0]);
    print_student_less_roll(root,roll_no);
}

void handle_roll_less_than(node* &root , string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_s = std::stoi (data[0]);
    int roll = std::stoi(data[1]);
    print_student_between_roll(root,roll_s,roll_l);
}

void handle_CGPA_greater_than(node* &root , string line) {
    std::vector<std::string> data = split_by_comma(line);
    float cgpa = std::stof (data[0]);
    print_student_greater_cgpa(root,cgpa);
}

void handle_CGPA_lesser_than(node* &root , string line) {
    std::vector<std::string> data = split_by_comma(line);
    float cgpa = std::stof (data[0]);
    print_student_lesser_cgpa(root,cgpa);
}

void handle_CGPA_between_than(node* &root , string line) {
    std::vector<std::string> data = split_by_comma(line);
    float cgpaf = std::stof (data[0]);
    float cgpal = std::stof (data[1]);
    print_student_between_cgpa(root,cgpaf,cgpal);
}

void handle_delete_student(node* & root, std::string line) {
    int roll_no = std::stoi(line);
    delete_student(root, roll_no);
}

void handle_add_course(node*& root, std::string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi(data[0]);
    CodeMarks course{std::stoi(data[1]), std::stof(data[2])};
    add_course(root, roll_no ,std::stoi(data[1]), std::stof(data[2])); // check again
}

void handle_modify_course(node*& root, std::string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi(data[0]);
    int course_id = std::stoi(data[1]);
    float new_grade = std::stof(data[2]);
    modify_course(root, roll_no, course_id, new_grade);
}

void handle_delete_course(node*& root, std::string line) {
    std::vector<std::string> data = split_by_comma(line);
    int roll_no = std::stoi(data[0]);
    int course_id = std::stoi(data[1]);
    delete_course(root, roll_no, course_id);
}
