//
// Created by Yakovenko Ivan on 22.06.2023.
//
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
#ifndef LABA6_MULTISET_H
#define LABA6_MULTISET_H

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(const T& value, Node<T>* p) {
        data = value;
        left = nullptr;
        right = nullptr;
        parent = p;
    }
};

template <typename T>
class Multiset {
private:
    Node<T>* root;

    bool searchRecursive(Node<T>* node, const T& value);
    Node<T>* insertRecursive(Node<T>* node, const T& value, Node<T>* parent);
    void clearRecursive(Node<T>* node);
    void unionSetRecursive(Node<T>* node, Multiset<T>& resultSet);
    Node<T>* FindMin(Node<T>* node);
    Node<T>* FindMax(Node<T>* node);
    void copyRecursive(Node<T>* node);

public:
    Multiset() { root = nullptr; }

    bool empty() { return root == nullptr; }

    bool search(const T& value) { return searchRecursive(root, value); }

    void insert(const T& value) { root = insertRecursive(root, value, nullptr); }

    Node<T>* begin() { return FindMin(root); }

    Node<T>* end() { return FindMax(root); }

    void clear();

    Multiset<T> unionSet(const Multiset<T>& otherSet);

    Multiset<T>& operator=(const Multiset<T>& other);

    class MultisetIterator;
};



#endif //LABA6_MULTISET_H
