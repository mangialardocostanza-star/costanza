#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <class T>
class Node {
private:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int heigth;
    int fe;

public:
    Node(T, Node<T>*, Node<T>*);
    ~Node();

    bool isLeaf();
    Node<T>* getChildren(int);
    void setChildren(Node<T>*, Node<T>*);
    void setData(T);
    T getData();
    void print();

    void setFe();
    void setFe(int);
    int getFe();

    void setHeigth(int);
    int getHeigth();
    int calculate_Heigth(Node<T>*);

    void setRight(Node<T>*);
    void setLeft(Node<T>*);
    int autoHeight();

    int id;
    std::string name;
    std::string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;
};

#endif
