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
template <class T>
Node<T>* Tree<T>::findFirstSuccessorAliveAndFree(Node<T>* node) {
    if (!node) return nullptr;
    if (!node->is_dead && !node->in_jail && node != current_boss) return node;

    Node<T>* found = findFirstSuccessorAliveAndFree(node->left);
    if (found) return found;
    return findFirstSuccessorAliveAndFree(node->right);
}

template <class T>
Node<T>* Tree<T>::findSuccessorInSubtree(Node<T>* node) {
    if (!node) return nullptr;

    Node<T>* queue[200];
    int front = 0, rear = 0;
    queue[rear++] = node;

    while (front < rear) {
        Node<T>* current = queue[front++];
        if (!current->is_dead && !current->in_jail && current != current_boss)
            return current;
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    return nullptr;
}

template <class T>
Node<T>* Tree<T>::findSuccessorFromBoss(Node<T>* boss) {
    if (!boss) return nullptr;
    Node<T>* successor = findSuccessorInSubtree(boss->left);
    if (successor) return successor;
    return findSuccessorInSubtree(boss->right);
}

template <class T>
Node<T>* Tree<T>::findSuccessorFromOtherChild(Node<T>* boss) {
    if (!boss || !boss->parent) return nullptr;
    Node<T>* parent = boss->parent;
    Node<T>* otherChild = (parent->left == boss) ? parent->right : parent->left;
    if (otherChild) return findSuccessorInSubtree(otherChild);
    return nullptr;
}

template <class T>
Node<T>* Tree<T>::findSuccessorFromPartner(Node<T>* boss) {
    if (!boss || !boss->parent) return nullptr;
    Node<T>* parent = boss->parent;
    Node<T>* partner = (parent->left == boss) ? parent->right : parent->left;
    if (partner && !partner->is_dead && !partner->in_jail && partner != current_boss) {
        bool hasSuccessor = (findSuccessorInSubtree(partner->left) != nullptr) ||
            (findSuccessorInSubtree(partner->right) != nullptr);
        if (!hasSuccessor) return partner;
    }
    return nullptr;
}

template <class T>
Node<T>* Tree<T>::findSuccessorFromUncle(Node<T>* boss) {
    if (!boss || !boss->parent || !boss->parent->parent) return nullptr;
    Node<T>* grandparent = boss->parent->parent;
    Node<T>* uncle = (grandparent->left == boss->parent) ? grandparent->right : grandparent->left;
    if (uncle) {
        Node<T>* successor = findSuccessorInSubtree(uncle);
        if (successor) return successor;
        if (!uncle->is_dead && !uncle->in_jail && uncle != current_boss) return uncle;
    }
    return findSuccessorFromOtherChild(grandparent);
}

template <class T>
Node<T>* Tree<T>::findSuccessorFromClosestBossWithTwoSuccessors(Node<T>* startNode) {
    if (!startNode) return nullptr;
    Node<T>* nodeQueue[200];
    int levelQueue[200];
    int front = 0, rear = 0;
    nodeQueue[rear] = startNode;
    levelQueue[rear] = 0;
    rear++;

    Node<T>* bestBoss = nullptr;
    int bestLevel = -1;

    while (front < rear) {
        Node<T>* current = nodeQueue[front];
        int level = levelQueue[front];
        front++;

        int aliveFreeCount = 0;
        Node<T>* firstCandidate = nullptr;
        if (current->left && !current->left->is_dead && !current->left->in_jail && current->left != current_boss) {
            aliveFreeCount++;
            firstCandidate = current->left;
        }
        if (current->right && !current->right->is_dead && !current->right->in_jail && current->right != current_boss) {
            aliveFreeCount++;
            if (!firstCandidate) firstCandidate = current->right;
        }
        if (aliveFreeCount >= 2 && (bestLevel == -1 || level < bestLevel)) {
            bestBoss = firstCandidate;
            bestLevel = level;
        }
        if (current->parent) {
            nodeQueue[rear] = current->parent;
            levelQueue[rear] = level + 1;
            rear++;
        }
    }
    return bestBoss;
}

template <class T>
Node<T>* Tree<T>::findSuccessorInJailRecursive(Node<T>* node, Node<T>* originalBoss) {
    if (!node) return nullptr;
    if (node->in_jail && !node->is_dead && node != originalBoss && node != current_boss)
        return node;
    Node<T>* found = findSuccessorInJailRecursive(node->left, originalBoss);
    if (found) return found;
    return findSuccessorInJailRecursive(node->right, originalBoss);
}

template <class T>
Node<T>* Tree<T>::findSuccessorInJail(Node<T>* startNode) {
    Node<T>* temp = startNode;
    while (temp) {
        Node<T>* found = findSuccessorInJailRecursive(temp, startNode);
        if (found) return found;
        temp = temp->parent;
    }
    return nullptr;
}

template <class T>
Node<T>* Tree<T>::findSuccessorBreadthFirst(Node<T>* startNode, bool includeJail) {
    if (!startNode) return nullptr;
    Node<T>* queue[200];
    int front = 0, rear = 0;
    queue[rear++] = startNode;
    while (front < rear) {
        Node<T>* current = queue[front++];
        if (includeJail) {
            if (current->in_jail && !current->is_dead && current != current_boss)
                return current;
        }
        else {
            if (!current->is_dead && !current->in_jail && current != current_boss)
                return current;
        }
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    return nullptr;
}

template <class T>
void Tree<T>::updateBossStatus(Node<T>* newBoss) {
    if (!newBoss) return;
    if (current_boss) {
        current_boss->is_boss = false;
        current_boss->was_boss = true;
    }
    newBoss->is_boss = true;
    current_boss = newBoss;

    cout << " NUEVO JEFE ASIGNADO: " << newBoss->name << " " << newBoss->last_name
        << " (ID: " << newBoss->id << ") ***" << endl;

    ofstream file("../bin/data.csv");
    if (file.is_open()) {
        file << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
        saveToCSV(root, file);
        file.close();
        cout << "los cambios se  guardaron en data.csv" << endl;
    }
}

template <class T>
void Tree<T>::saveToCSV(Node<T>* node, ofstream& file) {
    if (!node) return;
    saveToCSV(node->left, file);
    file << node->id << "," << node->name << "," << node->last_name << ","
        << node->gender << "," << node->age << "," << node->id_boss << ","
        << (node->is_dead ? 1 : 0) << "," << (node->in_jail ? 1 : 0) << ","
        << (node->was_boss ? 1 : 0) << "," << (node->is_boss ? 1 : 0) << "\n";
    saveToCSV(node->right, file);
}

template <class T>
void Tree<T>::checkAndUpdateSuccession() {
    if (!current_boss) return;
    bool needSuccession = false;
    string reason;

    if (current_boss->is_dead) {
        needSuccession = true;
        reason = "murio";
    }
    else if (current_boss->in_jail) {
        needSuccession = true;
        reason = "fue encarcelado";
    }
    else if (current_boss->age >= 70) {
        needSuccession = true;
        reason = "cumplio 70 años";
    }

    if (!needSuccession) return;

    cout << "=== El jefe actual " << current_boss->name << " " << current_boss->last_name
        << " " << reason << " ===" << endl;

    Node<T>* successor = nullptr;
    successor = findSuccessorFromBoss(current_boss);
    if (!successor) successor = findSuccessorFromOtherChild(current_boss);
    if (!successor) successor = findSuccessorFromPartner(current_boss);
    if (!successor) successor = findSuccessorFromUncle(current_boss);
    if (!successor) successor = findSuccessorFromClosestBossWithTwoSuccessors(current_boss);
    if (!successor) successor = findSuccessorInJail(current_boss);
    if (!successor) successor = findSuccessorBreadthFirst(root, false);
    if (!successor) successor = findSuccessorBreadthFirst(root, true);

    if (successor) updateBossStatus(successor);
    else cout << "Error critico: No se pudo encontrar ningun sucesor" << endl;
}

template <class T>
void Tree<T>::printSuccessionLinePreorder(Node<T>* node, int level) {
    if (!node) return;
    if (!node->is_dead) {
        for (int i = 0; i < level; i++) cout << "  ";
        cout << "├─ ID: " << node->id << " | " << node->name << " " << node->last_name
            << " | " << (node->gender == 'H' ? "Hombre" : "Mujer")
            << " | Edad: " << node->age;
        if (node->in_jail) cout << " | [ENCARCELADO]";
        if (node->is_boss) cout << " | [JEFE ACTUAL]";
        cout << endl;
    }
    if (node->left || node->right) {
        printSuccessionLinePreorder(node->left, level + 1);
        printSuccessionLinePreorder(node->right, level + 1);
    }
}

template <class T>
void Tree<T>::showSuccessionLine() {
    cout << "=== LINEA DE SUCESION (solo miembros vivos) ===" << endl;
    cout << "Jefe actual: " << current_boss->name << " " << current_boss->last_name << endl;
    cout << "==============================================" << endl;
    printSuccessionLinePreorder(root, 0);
    cout << "==============================================" << endl;
}

template <class T>
void Tree<T>::updateNodeData(int id) {
    Node<T>* node = findNode(root, id);
    if (!node) {
        cout << "ID no encontrado" << endl;
        return;
    }

    cout << "--- editando miembro: " << node->name << " " << node->last_name << " ---" << endl;
    cout << "no se puede modificar ID ni ID_BOSS" << endl;
    cout << "dejar en blanco para mantener valor actual" << endl;

    string input;
    cout << "Nombre actual (" << node->name << "): ";
    getline(cin, input);
    if (!input.empty()) node->name = input;

    cout << "Apellido actual (" << node->last_name << "): ";
    getline(cin, input);
    if (!input.empty()) node->last_name = input;

    cout << "Genero actual (" << node->gender << "): ";
    getline(cin, input);
    if (!input.empty()) node->gender = input[0];

    cout << "Edad actual (" << node->age << "): ";
    getline(cin, input);
    if (!input.empty()) node->age = stoi(input);

    cout << "¿Ha muerto? (0=No, 1=Si) actual (" << node->is_dead << "): ";
    getline(cin, input);
    if (!input.empty()) node->is_dead = stoi(input);

    cout << "¿Esta encarcelado? (0=No, 1=Si) actual (" << node->in_jail << "): ";
    getline(cin, input);
    if (!input.empty()) node->in_jail = stoi(input);

    ofstream file("../bin/data.csv");
    if (file.is_open()) {
        file << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";
        saveToCSV(root, file);
        file.close();
        cout << "Datos guardados correctamente en data.csv" << endl;
    }

    if (node->is_boss && (node->is_dead || node->in_jail || node->age >= 70)) {
        cout << "\nEl jefe ha sido modificado. Verificando sucesion..." << endl;
        checkAndUpdateSuccession();
    }
    cout << "datos actualizados correctamente" << endl;
}

template <class T>
void Tree<T>::run() {
    int option;
    string input;

    do {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║   SISTEMA DE SUCESION MAFIOSA     ║" << endl;
        cout << "╠════════════════════════════════════╣" << endl;
        cout << "║ 1. Mostrar linea de sucesion       ║" << endl;
        cout << "║ 2. Verificar estado del jefe       ║" << endl;
        cout << "║ 3. Editar datos de un miembro      ║" << endl;
        cout << "║ 4. Salir                           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "Opcion: ";
        getline(cin, input);

        if (input.empty()) continue;
        try {
            option = stoi(input);
        }
        catch (...) {
            cout << "Opcion invalida" << endl;
            continue;
        }

        switch (option) {
        case 1:
            showSuccessionLine();
            break;
        case 2:
            checkAndUpdateSuccession();
            showSuccessionLine();
            break;
        case 3: {
            int id;
            cout << "Ingrese ID del miembro a editar: ";
            getline(cin, input);
            try {
                id = stoi(input);
                updateNodeData(id);
            }
            catch (...) {
                cout << "ID invalido" << endl;
            }
            break;
        }
        case 4:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
        }
    } while (option != 4);
}

template class Tree<int>;

