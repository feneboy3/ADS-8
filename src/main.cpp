// Copyright 2021 NNTU-CS
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);  // NOLINT
void printFreq(BST<std::string>& tree);  // NOLINT

int main() {
    BST<std::string> tree;

    makeTree(tree, "src/war_peace.txt");

    printFreq(tree);

    return 0;
}
