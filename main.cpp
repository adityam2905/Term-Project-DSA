#include "filehandler.h"

int main() {
    AVL tree;  // Create an AVL tree

    // Path to the input file
    const char* filename = "input_avl.txt";

    // Process the file and populate the AVL tree
    process_file(filename, tree);

    return 0;
}
