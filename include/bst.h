// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>

template <typename T>
class BST {
public:
    // Структура узла дерева
    struct Node {
        T value;       // Само слово
        int count;     // Счетчик повторений
        Node* left;
        Node* right;
        
        // Конструктор узла
        Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    // Рекурсивный помощник для вставки
    Node* insertHelper(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->value) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->value) {
            node->right = insertHelper(node->right, val);
        } else {
            // Если слово уже есть в дереве, просто увеличиваем счетчик
            node->count++;
        }
        return node;
    }

    // Рекурсивный помощник для измерения глубины
    int depthHelper(Node* node) {
        if (node == nullptr) return 0;
        int leftDepth = depthHelper(node->left);
        int rightDepth = depthHelper(node->right);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }

    // Рекурсивный помощник для поиска
    bool searchHelper(Node* node, T val) {
        if (node == nullptr) return false;
        if (node->value == val) return true;
        if (val < node->value) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }

    // Очистка памяти
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

    // Основные методы, которые мы вызываем снаружи
    void insert(T val) {
        root = insertHelper(root, val);
    }

    int depth() {
        return depthHelper(root);
    }

    bool search(T val) {
        return searchHelper(root, val);
    }

    // Метод для получения корня (понадобится для обхода в alg.cpp)
    Node* getRoot() {
        return root;
    }
};

#endif  // INCLUDE_BST_H_
