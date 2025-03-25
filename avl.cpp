// avl.cpp
#include "avl.h"


int AVL::getheight(Node* root) {
   if (!root) return 0;
   return root->height;
}


int AVL::getbalance(Node* root) {
   return getheight(root->left) - getheight(root->right);
}


Node* AVL::rightrotate(Node* root) {
   Node* child = root->left;
   Node* childRight = child->right;
   child->right = root;
   root->left = childRight;
   root->height = 1 + std::max(getheight(root->left), getheight(root->right));
   child->height = 1 + std::max(getheight(child->left), getheight(child->right));
   return child;
}


Node* AVL::leftrotate(Node* root) {
   Node* child = root->right;
   Node* childLeft = child->left;
   child->left = root;
   root->right = childLeft;
   root->height = 1 + std::max(getheight(root->left), getheight(root->right));
   child->height = 1 + std::max(getheight(child->left), getheight(child->right));
   return child;
}


Node* AVL::insert(Node* root, int key, const std::string& name, float cgpa, int numCourses, const std::vector<Course*>& courses) {
   // Base case: If the tree is empty, create a new node with the given data
   if (!root) {
       // Here we create a new Node with the student info and the courses vector
       return new Node(key, name, cgpa, numCourses, courses);  // Pass courses as part of Node construction
   }


   // Recursively insert into left or right sub-tree
   if (key < root->value) {
       root->left = insert(root->left, key, name, cgpa, numCourses, courses);
   } else if (key > root->value) {
       root->right = insert(root->right, key, name, cgpa, numCourses, courses);
   } else {
       return root;  // No duplicates allowed, so return the current root
   }


   // Update the height of the ancestor node
   root->height = 1 + std::max(getheight(root->left), getheight(root->right));


   // Balance the tree if necessary
   int balance = getbalance(root);


   // Left Left Case
   if (balance > 1 && key < root->left->value) {
       return rightrotate(root);
   }


   // Right Right Case
   if (balance < -1 && key > root->right->value) {
       return leftrotate(root);
   }


   // Left Right Case
   if (balance > 1 && key > root->left->value) {
       root->left = leftrotate(root->left);
       return rightrotate(root);
   }


   // Right Left Case
   if (balance < -1 && key < root->right->value) {
       root->right = rightrotate(root->right);
       return leftrotate(root);
   }


   // Return the (possibly updated) root node
   return root;
}
Node* AVL::findNodeByRollNumber(Node* root, int roll_no) {
   if (!root) {
       std::cout << "Node not found: " << roll_no << std::endl;
       return nullptr;
   }
   if (root->value == roll_no) {
       std::cout << "Node found: " << roll_no << std::endl;
       return root;
   }
   if (roll_no < root->value)
       return findNodeByRollNumber(root->left, roll_no);
   return findNodeByRollNumber(root->right, roll_no);
}


void AVL::inorder(Node* root) {
   if (!root) return;
   inorder(root->left);
   std::cout << "Student Roll No: " << root->value << ", Name: " << root->name << ", CGPA: " << root->cgpa << "\n";
   for (const auto& course : root->courses) {
       std::cout << "  Course Code: " << course->courseCode << ", Marks: " << course->marks << "\n";
   }
   inorder(root->right);
}
Node* AVL::deleteNode(Node* &root, int roll_no) {
   // standard BST delete
   if (root == nullptr) return root;


   // go left if roll_no is smaller
   if (roll_no < root->value) {
       root->left = deleteNode(root->left, roll_no);
   }
   // go right if roll_no is greater
   else if (roll_no > root->value) {
       root->right = deleteNode(root->right, roll_no);
   }
   // node to be deleted found
   else {
       // one or no child
       if (root->left == nullptr || root->right == nullptr) {
           Node* temp = root->left ? root->left : root->right;


           // free courses linked to this node
           for (Course* course : root->courses) {
               delete course;
           }


           delete root;
           return temp;
       }


       // node with two children find inorder successor
       Node* temp = minValueNode(root->right);


       // copy successor data
       root->value = temp->value;
       root->name = temp->name;
       root->cgpa = temp->cgpa;


       // clear old course list copy new one
       root->courses.clear();
       for (Course* course : temp->courses) {
           root->courses.push_back(new Course(course->courseCode, course->marks));
       }


       // delete successor
       root->right = deleteNode(root->right, temp->value);
   }


   // update height
   root->height = std::max(getheight(root->left), getheight(root->right)) + 1;


   // check balance factor
   int balance = getbalance(root);


   // left heavy
   if (balance > 1 && getbalance(root->left) >= 0) return rightrotate(root);


   // right heavy
   if (balance < -1 && getbalance(root->right) <= 0) return leftrotate(root);


   // left right case
   if (balance > 1 && getbalance(root->left) < 0) {
       root->left = leftrotate(root->left);
       return rightrotate(root);
   }


   // right left case
   if (balance < -1 && getbalance(root->right) > 0) {
       root->right = rightrotate(root->right);
       return leftrotate(root);
   }


   return root;
}


Node* AVL::minValueNode(Node* node) {
   Node* current = node;


   // Loop down to find the leftmost leaf
   while (current && current->left != nullptr) {
       current = current->left;
   }


   return current;
}


void AVL::printTree() {
   // Inorder traversal prints the nodes in sorted order
   inorder(root);
   std::cout << "\n-------------------------------------\n";
}

