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
    if (root == nullptr) {
        return nullptr;  // Return null if the tree is empty or we've reached a leaf
    }

    if (root->value == roll_no) {
        return root;  // Found the node with the given roll number
    } else if (roll_no < root->value) {
        // If the roll number is smaller, search in the left subtree
        return findNodeByRollNumber(root->left, roll_no);
    } else {
        // If the roll number is larger, search in the right subtree
        return findNodeByRollNumber(root->right, roll_no);
    }
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
Node* AVL::deleteNode(Node* root, int roll_no) {
    // Step 1: Perform the standard BST delete
    if (root == nullptr) {
        return root;
    }

    // If the roll_no is smaller, go to the left subtree
    if (roll_no < root->value) {
        root->left = deleteNode(root->left, roll_no);
    }
    // If the roll_no is greater, go to the right subtree
    else if (roll_no > root->value) {
        root->right = deleteNode(root->right, roll_no);
    }
    // If this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;  // Free memory
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;  // Free memory
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->value = temp->value;
        root->name = temp->name;
        root->cgpa = temp->cgpa;
        root->courses = temp->courses;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->value);
    }

    // Step 2: Update the height of the current node
    root->height = std::max(getheight(root->left), getheight(root->right)) + 1;

    // Step 3: Get the balance factor to check if this node became unbalanced
    int balance = getbalance(root);

    // If the node is unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && getbalance(root->left) >= 0) {
        return rightrotate(root);
    }

    // Right Right Case
    if (balance < -1 && getbalance(root->right) <= 0) {
        return leftrotate(root);
    }

    // Left Right Case
    if (balance > 1 && getbalance(root->left) < 0) {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }

    // Right Left Case
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