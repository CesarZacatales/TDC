#include <iostream>
#include "node.hpp" // Supongo que esta es la cabecera para la clase Node

using namespace std;

// Definición de la clase BSTNode
class BSTNode {
public:
    int id;         // Identificador del nodo
    Node* node;     // Puntero al objeto Node asociado a este nodo del árbol
    BSTNode* left;  // Puntero al hijo izquierdo del nodo
    BSTNode* right; // Puntero al hijo derecho del nodo

    // Constructor de BSTNode
    BSTNode(int id, Node* node) : id(id), node(node), left(nullptr), right(nullptr) {}
};

// Definición de la clase BST (árbol binario de búsqueda)
class BST {
private:
    BSTNode* root; // Puntero a la raíz del árbol

    // Función auxiliar para insertar un nodo en el árbol
    void insertHelper(BSTNode*& node, int id, Node* nodePtr) {
        if (node == nullptr) {
            node = new BSTNode(id, nodePtr);
        } else if (id < node->id) {
            insertHelper(node->left, id, nodePtr);
        } else {
            insertHelper(node->right, id, nodePtr);
        }
    }

    // Función auxiliar para imprimir el árbol en orden
    void printInOrderHelper(BSTNode* node) {
        if (node != nullptr) {
            printInOrderHelper(node->left);
            cout << "Node: " << node->node->get_ID() << ", x= " << node->node->get_x_coordinate() << ", y= " << node->node->get_y_coordinate() << "\n";
            printInOrderHelper(node->right);
        }
    }

public:
    // Constructor de BST
    BST() : root(nullptr) {}

    // Método para insertar un nodo en el árbol
    void insert(int id, Node* nodePtr) {
        insertHelper(root, id, nodePtr);
    }

    // Método para imprimir el árbol en orden
    void printInOrder() {
        printInOrderHelper(root);
    }
};
