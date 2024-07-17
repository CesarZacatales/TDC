class Element {
    private:
        int ID;
        Node* node1;
        Node* node2;
        Node* node3;
        Node* node4;//Se agrega un cuarto nodo para el caso de elementos de 4 nodos en 3D

    public:
    //Se agrega un cuarto nodo para el caso de elementos de 4 nodos en 3D
        Element (int identifier, Node* first_node, Node* second_node, Node* third_node, Node* fourth_node){
            ID = identifier;
            node1 = first_node;
            node2 = second_node;
            node3 = third_node;
            node4 = fourth_node;//Se agrega un cuarto nodo para el caso de elementos de 4 nodos en 3D
        }

        void set_ID(int identifier){
            ID = identifier;
        }
        int get_ID(){
            return ID;
        }

        void set_node1(Node* node){
            node1 = node;
        }
        Node* get_node1(){
            return node1;
        }

        void set_node2(Node* node){
            node2 = node;
        }
        Node* get_node2(){
            return node2;
        }

        void set_node3(Node* node){
            node3 = node;
        }
        Node* get_node3(){
            return node3;
        }
        
        void set_node4(Node* node){//set para el cuarto nodo
            node4 = node;
        }

        Node* get_node4(){//get para el cuarto nodo
            return node4;
        }
};