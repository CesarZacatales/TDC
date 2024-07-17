#include <fstream>

void read_input(string filename, Mesh* M){
    string line;
    float P_bar, P_hat;
    int num_nodes, num_elements, num_condition_1, num_condition_2;
    ifstream dat_file(filename+".dat");

    dat_file >> P_bar >> P_hat >> num_nodes >> num_elements >> num_condition_1 >> num_condition_2;
    
    //M->set_problem_data(k,Q);
    M->set_quantities(num_nodes,num_elements,num_condition_1,num_condition_2);

    M->init_arrays();

    dat_file >> line;

    for(int i = 0; i < num_nodes; i++){
        int id;
        float x, y;
        dat_file >> id >> x >> y;
        M->insert_node(new Node(id,x,y), i);
        M->insert_node_BST(M->get_node(i)); // Insertar nodo en el árbol binario de búsqueda
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_elements; i++){
        int id, node1_id, node2_id, node3_id;
        dat_file >> id >> node1_id >> node2_id >> node3_id;
        M->insert_element(new Element(id, M->get_node(node1_id-1), M->get_node(node2_id-1), M->get_node(node3_id-1)), i);
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_condition_1; i++){
        int id;
        dat_file >> id;
        M->insert_condition_1(new Condition(M->get_node(id-1), P_bar), i);
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_condition_2; i++){
        int id;
        dat_file >> id;
        M->insert_condition_2(new Condition(M->get_node(id-1), P_hat), i);
    }

    dat_file.close();
}

void write_output(string filename, Vector* P){
    ofstream res_file(filename+".post.res");
    
    res_file << "GiD Post Results File 1.0\n";

    int n = P->get_size();

    res_file << "Result \"P\" \"Load Case 1\" " << 1 << " Scalar OnNodes\n";
    res_file << "ComponentNames \"P\"\n";
    res_file << "Values\n";

    for(int i = 0; i < n; i++)
        res_file << i+1 << "     " << P->get(i) << "\n";

    res_file << "End values\n";

    res_file.close();
}
