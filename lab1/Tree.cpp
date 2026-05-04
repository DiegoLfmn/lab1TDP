#include "Tree.h"

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    destroyRec(root);
}

// limpiamos memoria de nodos

void Tree::destroyRec(TreeNode* node) {
    if (node != nullptr) {
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }
}



int Tree::compareStates(State* a, State* b){

    if(a->numBloques != b->numBloques){
        if(a->numBloques == b->numBloques){
            return -1;
        }else{
            return 1;
        }
        //return (a->numBloques < b->numBloques) ? -1 : 1;
    }

    for (int i = 0; i < a->numBloques; i++){
        if (a->bloques[i].id != b->bloques[i].id){
            return (a->bloques[i].id < b->bloques[i].id) ? -1 : 1;
        }
        if (a->bloques[i].x != b->bloques[i].x){
            return (a->bloques[i].x < b->bloques[i].x) ? -1 : 1;
        }
        if (a->bloques[i].y != b->bloques[i].y){
            return (a->bloques[i].y < b->bloques[i].y) ? -1 : 1;
        }
    }
    return 0;
}


void Tree::insert(State* estado){
    root = insertRec(root, estado);
}

TreeNode* Tree::insertRec(TreeNode* node, State* estado){
    // si llegamos a un nodo nulo, insertamos el nuevo estado aquí
    if (node == nullptr){
        return new TreeNode(estado);
    }

    int cmp = compareStates(estado, node->estado);

    if (cmp < 0){
        node->left = insertRec(node->left, estado);
    } else if (cmp > 0){
        node->right = insertRec(node->right, estado);
    }
    // si cmp == 0, el estado ya existe en el árbol, no hacemos nada
    return node;
}


bool Tree::contains(State* estado){
    return containsRec(root, estado);
}

bool Tree::containsRec(TreeNode* node, State* estado){
    // si llegamos a un nodo nulo, el estado no está en el árbol
    if (node == nullptr){
        return false;
    }
    int cmp = compareStates(estado, node->estado);
    if (cmp == 0){
        return true; // encontramos el estado
    } else if (cmp < 0){
        return containsRec(node->left, estado);
    } else {
        return containsRec(node->right, estado);
    }
}