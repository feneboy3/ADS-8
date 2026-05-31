// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>

template <typename T>
class BST {
 public:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;

        explicit Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    Node* insertHelper(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->value) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->value) {
            node->right = insertHelper(node->right, val);
        } else {
            node->count++;
        }
        return node;
    }

    int depthHelper(Node* node) {
        if (node == nullptr) return 0;
        int leftDepth = depthHelper(node->left);
        int rightDepth = depthHelper(node->right);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }

    int searchHelper(Node* node, T val) {
        if (node == nullptr) return 0;
        if (node->value == val) return node->count;
        if (val < node->value) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }

    void destroyHelper(Node* node) {
        if (node != nullptr) {
            destroyHelper(node->left);
            destroyHelper(node->right);
            delete node;
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        destroyHelper(root);
    }

    void insert(T val) {
        root = insertHelper(root, val);
    }

    int depth() {
        int d = depthHelper(root);
        return d > 0 ? d - 1 : 0;
    }

    int search(T val) {
        return searchHelper(root, val);
    }

    Node* getRoot() {
        return root;
    }
};

#endif  // INCLUDE_BST_H_
