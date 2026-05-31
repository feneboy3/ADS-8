// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    std::string current_word = "";

    while (!file.eof()) {
        int ch = file.get();
        if (ch == EOF) break;

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch += 32;
            }
            current_word += static_cast<char>(ch);
        } else {
            if (!current_word.empty()) {
                tree.insert(current_word);
                current_word = "";
            }
        }
    }

    if (!current_word.empty()) {
        tree.insert(current_word);
    }

    file.close();
}

void traverse(BST<std::string>::Node* node,
              std::vector<BST<std::string>::Node*>* nodes) {
    if (node == nullptr) return;
    traverse(node->left, nodes);
    nodes->push_back(node);
    traverse(node->right, nodes);
}

bool compareNodes(BST<std::string>::Node* a, BST<std::string>::Node* b) {
    return a->count > b->count;
}

void printFreq(BST<std::string>& tree) {
    std::vector<BST<std::string>::Node*> nodes;

    traverse(tree.getRoot(), &nodes);

    std::sort(nodes.begin(), nodes.end(), compareNodes);

    std::ofstream out("result/freq.txt");

    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i]->value << " " << nodes[i]->count << std::endl;
        if (out.is_open()) {
            out << nodes[i]->value << " " << nodes[i]->count << "\n";
        }
    }

    if (out.is_open()) {
        out.close();
    }
}
