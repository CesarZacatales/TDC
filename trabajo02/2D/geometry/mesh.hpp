#include "node.hpp"
#include "element.hpp"
#include "condition.hpp"
#include "bst.hpp"

enum quantity {NUM_NODES, NUM_ELEMENTS, NUM_CONDITION_1, NUM_CONDITION_2};

class Mesh {
    private:
        int quantities[4];
        Node** nodes;
        BST bst; // Árbol binario de búsqueda
        Element** elements;
        Condition** conditions_1;
        Condition** conditions_2;

    public:
        Mesh(){}

        ~Mesh(){
            free(nodes);
            free(elements);
            free(conditions_1);
            free(conditions_2);
        }
        void insert_node(Node* node) {
        bst.insert(node->get_ID(), node); // Insertar en el árbol de búsqueda binaria
        }

        void set_quantities(int num_nodes, int num_elements, int num_condition_1, int num_condition_2){
            quantities[NUM_NODES] = num_nodes;
            quantities[NUM_ELEMENTS] = num_elements;
            quantities[NUM_CONDITION_1] = num_condition_1;
            quantities[NUM_CONDITION_2] = num_condition_2;
        }
        int get_quantity(quantity position){
            return quantities[position];
        }

        void init_arrays(){
            nodes = (Node**) malloc(sizeof(Node*) * quantities[NUM_NODES]);
            elements = (Element**) malloc(sizeof(Element*) * quantities[NUM_ELEMENTS]);
            conditions_1 = (Condition**) malloc(sizeof(Condition*) * quantities[NUM_CONDITION_1]);
            conditions_2 = (Condition**) malloc(sizeof(Condition*) * quantities[NUM_CONDITION_2]);
        }
        // Método para insertar un nodo en el árbol binario de búsqueda
        void insert_node_BST(Node* node){
            bst.insert(node->get_ID(), node);
        }

        void insert_node(Node* node, int position){
            nodes[position] = node;
        }

        Node* get_node(int position){
            return nodes[position];
        }

        void insert_element(Element* element, int position){
            elements[position] = element;
        }
        Element* get_element(int position){
            return elements[position];
        }

        void insert_condition_1(Condition* condition_1, int position){
            conditions_1[position] = condition_1;
        }
        Condition* get_condition_1(int position){
            return conditions_1[position];
        }
        bool does_node_have_condition_1(int id){
            bool ans = false;
            for(int i = 0; i < quantities[NUM_CONDITION_1]; i++)
                if(conditions_1[i]->get_node()->get_ID() == id){
                    ans = true;
                    break;
                }
            return ans;
        }
        void insert_condition_2(Condition* condition_2, int position){
            conditions_2[position] = condition_2;
        }
        Condition* get_condition_2(int position){
            return conditions_2[position];
        }

        // Método para imprimir el árbol binario de búsqueda
        void showBST(){
            bst.printInOrder();
        }

        void report(){
            cout << "Number of nodes: " << quantities[NUM_NODES] << "\n";
            cout << "Number of elements: " << quantities[NUM_ELEMENTS] << "\n";
            cout << "Number of dirichlet boundary conditions: " << quantities[NUM_CONDITION_1] << "\n";
            cout << "Number of neumann boundary conditions: " << quantities[NUM_CONDITION_2] << "\n\n";
            cout << "List of nodes\n**********************\n";
            for(int i = 0; i < quantities[NUM_NODES]; i++)
                cout << "Node: " << nodes[i]->get_ID() << ", x= " << nodes[i]->get_x_coordinate() << ", y= " << nodes[i]->get_y_coordinate() << "\n";
            cout << "\nList of elements\n**********************\n";
            for(int i = 0; i < quantities[NUM_ELEMENTS]; i++){
                cout << "Element: " << elements[i]->get_ID() << ", Node 1= " << elements[i]->get_node1()->get_ID();
                cout << ", Node 2= " << elements[i]->get_node2()->get_ID() << ", Node 3= " << elements[i]->get_node3()->get_ID() << "\n";
            }
            cout << "\nList of Dirichlet boundary conditions\n**********************\n";
            for(int i = 0; i < quantities[NUM_CONDITION_1]; i++)
                cout << "Condition " << i+1 << ": " << conditions_1[i]->get_node()->get_ID() << ", Value= " << conditions_1[i]->get_value() << "\n";
            cout << "\nList of Neumann boundary conditions\n**********************\n";
            for(int i = 0; i < quantities[NUM_CONDITION_2]; i++)
                cout << "Condition " << i+1 << ": " << conditions_2[i]->get_node()->get_ID() << ", Value= " << conditions_2[i]->get_value() << "\n";
            cout << "\n";
        }
};