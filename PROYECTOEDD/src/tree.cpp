#include "tree.h"
#include <sstream>
#include <iostream>

using namespace std;

template <class T>
Tree<T>::Tree() {
    root = nullptr;
    current_boss = nullptr;
}

template <class T>
Tree<T>::~Tree() {
    delete root;
}

template <class T>
Node<T>* Tree<T>::findNode(Node<T>* node, int id) {
    if (!node) return nullptr;
    if (node->id == id) return node;

    Node<T>* found = findNode(node->left, id);
    if (found) return found;
    return findNode(node->right, id);
}

template <class T>
int Tree<T>::compareByAge(Node<T>* a, Node<T>* b) {
    if (!a) return 1;
    if (!b) return -1;
    return b->age - a->age;
}

template <class T>
void Tree<T>::addChildByAge(Node<T>* parent, Node<T>* child) {
    if (!parent) return;
    child->parent = parent;

    if (!parent->left) {
        parent->left = child;
    }
    else if (!parent->right) {
        if (compareByAge(child, parent->left) > 0) {
            parent->right = parent->left;
            parent->left = child;
        }
        else {
            parent->right = child;
        }
    }
    else {
        if (compareByAge(child, parent->left) > 0) {
            parent->right = parent->left;
            parent->left = child;
        }
        else if (compareByAge(child, parent->right) > 0) {
            parent->right = child;
        }
    }
}

template <class T>
bool Tree<T>::validateCSVFormat(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    getline(file, line);
    if (line != "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss") {
        file.close();
        return false;
    }

    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        stringstream ss(line);
        string token;
        int tokenCount = 0;
        while (getline(ss, token, ',')) tokenCount++;
        if (tokenCount != 10) {
            file.close();
            return false;
        }
    }
    file.close();
    return lineCount > 0;
}

template <class T>
bool Tree<T>::loadFromCSV(const string& filename) {
    if (!validateCSVFormat(filename)) {
        cout << "Error: El formato del CSV no es valido" << endl;
        return false;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string line;
    getline(file, line);

    struct TempNode {
        Node<T>* node;
        int id_boss;
        TempNode* next;
    };

    TempNode* head = nullptr;
    TempNode* tail = nullptr;
    int tempCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        int id, id_boss, age;
        string name, last_name;
        char gender;
        int is_dead, in_jail, was_boss, is_boss;

        try {
            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, last_name, ',');
            getline(ss, token, ','); gender = token[0];
            getline(ss, token, ','); age = stoi(token);
            getline(ss, token, ','); id_boss = stoi(token);
            getline(ss, token, ','); is_dead = stoi(token);
            getline(ss, token, ','); in_jail = stoi(token);
            getline(ss, token, ','); was_boss = stoi(token);
            getline(ss, token, ','); is_boss = stoi(token);
        }
        catch (...) {
            cout << "error: Datos corruptos  " << tempCount + 2 << endl;
            while (head) {
                TempNode* toDelete = head;
                head = head->next;
                delete toDelete->node;
                delete toDelete;
            }
            file.close();
            return false;
        }

        Node<T>* newNode = new Node<T>(id, nullptr, nullptr);
        newNode->id = id;
        newNode->name = name;
        newNode->last_name = last_name;
        newNode->gender = gender;
        newNode->age = age;
        newNode->id_boss = id_boss;
        newNode->is_dead = is_dead;
        newNode->in_jail = in_jail;
        newNode->was_boss = was_boss;
        newNode->is_boss = is_boss;

        TempNode* temp = new TempNode;
        temp->node = newNode;
        temp->id_boss = id_boss;
        temp->next = nullptr;

        if (!head) {
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
        tempCount++;

        if (is_boss == 1) {
            current_boss = newNode;
        }
    }

    file.close();

    if (tempCount == 0) {
        cout << "Error: El CSV esta vacio" << endl;
        return false;
    }

    TempNode* current = head;
    while (current) {
        if (current->id_boss == -1) {
            if (!root) root = current->node;
        }
        else {
            Node<T>* parent = findNode(root, current->id_boss);
            if (parent) addChildByAge(parent, current->node);
        }
        current = current->next;
    }

    while (head) {
        TempNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    if (!root) {
        cout << "error: No se encontró un nodo raiz" << endl;
        return false;
    }

    if (!current_boss) {
        current_boss = root;
        current_boss->is_boss = true;
    }

    cout << "datos cargados exitosamente. Total miembros: " << tempCount << endl;
    return true;
}

