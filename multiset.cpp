#include "multiset.h"

template <typename T>
bool Multiset<T>::searchRecursive(Node<T>* node, const T& value) {
    if (node == nullptr)
        return false;

    if (node->data == value)
        return true;

    if (value < node->data)
        return searchRecursive(node->left, value);
    else
        return searchRecursive(node->right, value);
}

template <typename T>
Node<T>* Multiset<T>::insertRecursive(Node<T>* node, const T& value, Node<T>* parent) {
    if (node == nullptr)
        return new Node<T>(value, parent);

    if (value <= node->data)
        node->left = insertRecursive(node->left, value, node);
    else if (value > node->data)
        node->right = insertRecursive(node->right, value, node);

    return node;
}

template <typename T>
void Multiset<T>::clearRecursive(Node<T>* node) {
    if (node == nullptr)
        return;

    clearRecursive(node->left);
    clearRecursive(node->right);

    delete node;
}
template <typename T>
void Multiset<T>::unionSetRecursive(Node<T>* node, Multiset<T>& resultSet) {
    if (node == nullptr)
        return;

    resultSet.insert(node->data);
    unionSetRecursive(node->left, resultSet);
    unionSetRecursive(node->right, resultSet);
}
template <typename T>
Node<T>* Multiset<T>::FindMin(Node<T>* node) {
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr)
        return node;

    return FindMin(node->left);
}
template <typename T>
Node<T>* Multiset<T>::FindMax(Node<T>* node) {
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr)
        return node;

    return FindMax(node->right);
}
template <typename T>
void Multiset<T>::copyRecursive(Node<T>* node) {
    if (node == nullptr)
        return;

    insert(node->data);

    copyRecursive(node->left);
    copyRecursive(node->right);
}

template <typename T>
void Multiset<T>::clear() {
    clearRecursive(root);
    root = nullptr;
}
template <typename T>
Multiset<T> Multiset<T>::unionSet(const Multiset<T>& otherSet) {
    Multiset<T> resultSet;
    unionSetRecursive(root, resultSet);
    unionSetRecursive(otherSet.root, resultSet);
    return resultSet;
}
template <typename T>
Multiset<T>& Multiset<T>::operator=(const Multiset<T>& other) {
    if (this == &other)
        return *this;
    clear();
    copyRecursive(other.root);
    return *this;
}

template <typename T>
class Multiset<T>::MultisetIterator {
private:
    Node<T>* current;

public:
    MultisetIterator(Node<T>* node) : current(node) {}

    Node<T>* operator->() const { return current; }

    Node<T>& operator*() const { return *current; }

    MultisetIterator& operator++() {
        if (current == nullptr)
            return *this;

        if (current->right != nullptr) {
            Node<T>* node = current->right;
            while (node != nullptr && node->left != nullptr) {
                node = node->left;
            }
            current = node;
            return *this;
        }

        Node<T>* parent = current->parent;
        while (parent != nullptr && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }

        current = parent;
        return *this;
    }

    bool operator==(const MultisetIterator& other) const { return current == other.current; }

    bool operator!=(const MultisetIterator& other) const { return !(*this == other); }
};
