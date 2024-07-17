#include <iostream>

using namespace std;

#include "geometry/mesh.hpp"
#include "math_utilities/matrix_operations.hpp"
#include "mef_utilities/mef_process.hpp"
#include "gid/input_output.hpp"

int main (int argc, char** argv) {
    if(argc != 3){
        cout << "Incorrect use of the program, it must be: mef filename\n";
        exit(EXIT_FAILURE);
    }

    Mesh M;

    cout << "Reading geometry and mesh data...\n\n";
    string filename(argv[1]);
    read_input(filename, &M);


    short num_nodes = M.get_quantity(NUM_NODES);
    short num_elements = M.get_quantity(NUM_ELEMENTS);
    Matrix K(num_nodes,num_nodes), local_Ks[num_elements];
    Vector b(num_nodes),           local_bs[num_elements];

        // Muestra el contenido del árbol binario de búsqueda
    cout << "Content of the Binary Search Tree:\n";
    M.showBST();
    cout << "\n";

    cout << "Creating local systems...\n\n";
    create_local_systems(local_Ks, local_bs, num_elements, &M);

    cout << "Performing Assembly...\n\n";
    assembly(&K, &b, local_Ks, local_bs, num_elements, &M);

    cout << "Applying Boundary Conditions 2...\n\n";
    apply_boundary_conditions_2(&b, &M);

    cout << "Applying Boundary Conditions 1...\n\n";
    apply_boundary_conditions_1(&K, &b, &M);

    cout << "Solving global system...\n\n";
    Vector P(b.get_size()), P_full(num_nodes);
    solve_system(&K, &b, &P, atoi(argv[2]));
    
    cout << "Preparing results...\n\n";
    merge_results_with_condition_1(&P, &P_full, num_nodes, &M);

    cout << "Writing output file...\n\n";
    write_output(filename, &P_full);

    return 0;
}
