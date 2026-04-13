#include "node.h"

template <class T>
Node<T>::Node(T data, Node<T>* right, Node<T>* left) {
    this->data = data;
    this->parent = nullptr;
    this->heigth = 0;
    this->fe = 0;

    if (right != NULL)
        this->right = right;
    else
        this->right = nullptr;

    if (left != NULL)
        this->left = left;
    else
        this->left = nullptr;
}

template <class T>
Node<T>::~Node() {
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
}

template <class T>
bool Node<T>::isLeaf() {
    return (right == NULL && left == NULL);
}

template <class T>
Node<T>* Node<T>::getChildren(int child) {
    switch (child) {
    case 0:
        return this->left;
    case 1:
        return this->right;
    }
    return NULL;
}

template <class T>
void Node<T>::setChildren(Node<T>* right, Node<T>* left) {
    if (right != NULL && left != NULL) {
        this->right = right;
        this->left = left;
    }
    else if (left != NULL) {
        this->left = left;
    }
    else if (right != NULL) {
        this->right = right;
    }
    else {
        this->right = NULL;
        this->left = NULL;
        heigth = 0;
    }
    this->heigth = autoHeight();
}

template <class T>
void Node<T>::setRight(Node<T>* right) {
    this->right = right;
    if (right != nullptr)
        right->parent = this;
    this->heigth = autoHeight();
}

template <class T>
void Node<T>::setLeft(Node<T>* left) {
    this->left = left;
    if (left != nullptr)
        left->parent = this;
    this->heigth = autoHeight();
}

template <class T>
int Node<T>::autoHeight() {
    int h_left = calculate_Heigth(this->left);
    int h_right = calculate_Heigth(this->right);
    return (h_left < h_right) ? h_right : h_left;
}

template <class T>
void Node<T>::setData(T data) {
    this->data = data;
}

template <class T>
T Node<T>::getData() {
    return this->data;
}

template <class T>
void Node<T>::print() {
    cout << this->data << " ";
}

template <class T>
void Node<T>::setFe() {
    if (this->right == NULL && this->left == NULL) {
        this->fe = 0;
    }
    else if (this->right != NULL && this->left != NULL) {
        this->fe = (this->right->heigth) - (this->left->heigth);
    }
    else if (this->right == NULL) {
        this->fe = -(this->left->heigth);
    }
    else if (this->left == NULL) {
        this->fe = (this->right->heigth);
    }
}

template <class T>
void Node<T>::setFe(int fe) {
    this->fe = fe;
}

template <class T>
int Node<T>::getFe() {
    return this->fe;
}

template <class T>
void Node<T>::setHeigth(int heigth) {
    this->heigth = heigth;
}

template <class T>
int Node<T>::getHeigth() {
    return heigth;
}

template <class T>
int Node<T>::calculate_Heigth(Node<T>* node) {
    if (node == NULL) return 0;
    else {
        int heigthLeft = calculate_Heigth(node->left);
        int heigthRigth = calculate_Heigth(node->right);
        if (heigthLeft > heigthRigth)
            return heigthLeft + 1;
        else
            return heigthRigth + 1;
    }
}

template class Node<int>;
