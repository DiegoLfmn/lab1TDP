#ifndef TREE_H
#define TREE_H

#include "State.h"

// estructura de cada hoja del árbol

struct TreeNode {
    State* estado; // estado del nodo
    TreeNode* left;
    TreeNode* right;
    // constructor
    TreeNode(State* estado) : estado(estado), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    TreeNode* root;


    // Funciones recursivas privadas
    TreeNode* insertRec(TreeNode* node, State* estado);
    bool containsRec(TreeNode* node, State* estado);
    void destroyRec(TreeNode* node);

    // comparar dos estados para determinar su orden en el árbol
    int compareStates(State* a, State* b);
public:
    Tree();
    ~Tree();
    //funciones públicas para usar en solver
    void insert(State* estado);
    bool contains(State* estado);
    
};

#endif // TREE_H