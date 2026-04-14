#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <string>
#include <fstream>

using namespace std;

template <class T>
class Tree {
private:
    Node<T>* root;
    Node<T>* current_boss;

    Node<T>* findNode(Node<T>* node, int id);
    int compareByAge(Node<T>* a, Node<T>* b);
    void addChildByAge(Node<T>* parent, Node<T>* child);
    bool validateCSVFormat(const string& filename);

    Node<T>* findFirstSuccessorAliveAndFree(Node<T>* node);
    Node<T>* findSuccessorInSubtree(Node<T>* node);
    Node<T>* findSuccessorFromBoss(Node<T>* boss);
    Node<T>* findSuccessorFromOtherChild(Node<T>* boss);
    Node<T>* findSuccessorFromPartner(Node<T>* boss);
    Node<T>* findSuccessorFromUncle(Node<T>* boss);
    Node<T>* findSuccessorFromClosestBossWithTwoSuccessors(Node<T>* startNode);
    Node<T>* findSuccessorInJailRecursive(Node<T>* node, Node<T>* originalBoss);
    Node<T>* findSuccessorInJail(Node<T>* startNode);
    Node<T>* findSuccessorBreadthFirst(Node<T>* startNode, bool includeJail);

    void updateBossStatus(Node<T>* newBoss);
    void saveToCSV(Node<T>* node, ofstream& file);
    void printSuccessionLinePreorder(Node<T>* node, int level);

public:
    Tree();
    ~Tree();
    bool loadFromCSV(const string& filename);
    void showSuccessionLine();
    void checkAndUpdateSuccession();
    void updateNodeData(int id);
    void run();
};

#endif
