
// Función para calcular el volumen del tetraedro
float calculate_volume(float x1, float y1, float z1, 
                             float x2, float y2, float z2, 
                             float x3, float y3, float z3, 
                             float x4, float y4, float z4) {
    float a = x1;
    float b = y1;
    float c = z1;
    float d = 1.0;

    float e = x2;
    float f = y2;
    float g = z2;
    float h = 1.0;

    float i = x3;
    float j = y3;
    float k = z3;
    float l = 1.0;

    float m = x4;
    float n = y4;
    float o = z4;
    float p = 1.0;

    // Determinante de la matriz 4x4
    float det = 
        a * (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) -
        b * (e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m)) +
        c * (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m)) -
        d * (e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m));

    float V = abs(det) / 6.0;
    return (V == 0 ? 0.000001f : V);
}

//Se calcula el jacobiano local para un elemento 3D
float calculate_local_jacobian(float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3,float x4, float y4, float z4){
    float a = x2 - x1;
    float b = x3 - x1;
    float c = x4 - x1;
    float d = y2 - y1;
    float e = y3 - y1;
    float f = y4 - y1;
    float g = z2 - z1;
    float h = z3 - z1;
    float i = z4 - z1;
    float J = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    return (J == 0 ? 0.000001f : J);
}

// Función para calcular la matriz B de orden 3x4 para 3D
void calculate_B(Matrix* B){
    B->set(-1,0,0);  B->set(1,0,1);  B->set(0,0,2); B->set(0, 0, 3);
    B->set(-1,1,0);  B->set(0,1,1);  B->set(1,1,2); B->set(0, 1, 3);
    B->set(-1,2,0);  B->set(0,2,1);  B->set(0,2,2); B->set(1, 2, 3);
}

// Función para calcular la matriz A de orden 3x3 para 3D
void calculate_local_A(Matrix* A, float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3,float x4, float y4, float z4){
    A->set((y3-y1)*(z4-z1)-(y4-y1)*(z3-z1),0,0);     A->set(-(x3-x1)*(z4-z1)+(x4-x1)*(z3-z1),0,1);  A->set((x3-x1)*(y4-y1)-(x4-x1)*(y3-y1),0,2);
    A->set(-(y2-y1)*(z4-z1)+(y4-y1)*(z2-z1),1,0);    A->set((x2-x1)*(z4-z1)-(x4-x1)*(z2-z1),1,1);   A->set(-(x2-x1)*(y4-y1)+(x4-x1)*(y2-y1),1,2);
    A->set((y2-y1)*(z3-z1)-(y3-y1)*(z2-z1),2,0);     A->set(-(x2-x1)*(z3-z1)+(x3-x1)*(z2-z1),2,1);  A->set((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1),2,2);
}

// Función para calcular la matriz K local 4x4 de un elemento para 3D
void create_local_K(Matrix* K, int element_id, Mesh* M){
    //Se inicializa la matriz K local con dimensiones 4x4
    K->set_size(4,4);

    float k = M->get_problem_data(THERMAL_CONDUCTIVITY);
    //Se añade cuarto nodo  y coordenadas faltante como la coordenada z
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate(),
          x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();
    float Volumen = calculate_volume(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    float J = calculate_local_jacobian(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    
    //Se calcula la matriz B y A locales con dimensiones 3x4 y 3x3 respectivamente para 3D
    Matrix B(3,4), A(3,3);
    calculate_B(&B);
    calculate_local_A(&A, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    //B.show(); A.show();

    //Se calcula la matriz B transpuesta y A transpuesta para 3D
    Matrix Bt(4,3), At(3,3);
    transpose(&B,3,4,&Bt);
    transpose(&A,3,3,&At);
    //Bt.show(); At.show();

    Matrix res1, res2, res3;
    product_matrix_by_matrix(&A,&B,&res1);
    product_matrix_by_matrix(&At,&res1,&res2);
    product_matrix_by_matrix(&Bt,&res2,&res3);
    //Dimensiones de la matriz K local 4x4
    product_scalar_by_matrix(k*Volumen/(J*J),&res3,4,4,K);

    //cout << "\t\tLocal matrix created for Element " << element_id+1 << ": "; K->show(); cout << "\n";
}

// Función para calcular el vector b local de un elemento para 3D
void create_local_b(Vector* b, int element_id, Mesh* M){
    //Se inicializa el vector b local con dimensiones 4x1
    b->set_size(4);

    float Q = M->get_problem_data(HEAT_SOURCE);
    //Se añade nodo 4 y coordenadas faltante como la coordenada z
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate(),
          x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();
    float J = calculate_local_jacobian(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    
    //Se calcula el vector b local con dimensiones 4x1 para 3D
    b->set(Q*J/24,0);
    b->set(Q*J/24,1);
    b->set(Q*J/24,2);
    b->set(Q*J/24,3);

    //cout << "\t\tLocal vector created for Element " << element_id+1 << ": "; b->show(); cout << "\n";
}

void create_local_systems(Matrix* Ks, Vector* bs, int num_elements, Mesh* M){
    for(int e = 0; e < num_elements; e++){
        cout << "\tCreating local system for Element " << e+1 << "...\n\n";
        create_local_K(&Ks[e],e,M);
        create_local_b(&bs[e],e,M);
    }
}

// Función para ensamblar la matriz K global a partir de las matrices K locales para 3D
void assembly_K(Matrix* K, Matrix* local_K, int index1, int index2, int index3, int index4){
    K->add(local_K->get(0,0),index1,index1);    K->add(local_K->get(0,1),index1,index2);    K->add(local_K->get(0,2),index1,index3);    K->add(local_K->get(0,3),index1,index4);
    K->add(local_K->get(1,0),index2,index1);    K->add(local_K->get(1,1),index2,index2);    K->add(local_K->get(1,2),index2,index3);    K->add(local_K->get(1,3),index2,index4);
    K->add(local_K->get(2,0),index3,index1);    K->add(local_K->get(2,1),index3,index2);    K->add(local_K->get(2,2),index3,index3);    K->add(local_K->get(2,3),index3,index4);
    K->add(local_K->get(3,0),index4,index1);    K->add(local_K->get(3,1),index4,index2);    K->add(local_K->get(3,2),index4,index3);    K->add(local_K->get(3,3),index4,index4);
}

// Función para ensamblar el vector b global a partir de los vectores b locales para 3D
void assembly_b(Vector* b, Vector* local_b, int index1, int index2, int index3, int index4){
    b->add(local_b->get(0),index1);
    b->add(local_b->get(1),index2);
    b->add(local_b->get(2),index3);
    b->add(local_b->get(3),index4);
}

void assembly(Matrix* K, Vector* b, Matrix* Ks, Vector* bs, int num_elements, Mesh* M){
    K->init();
    b->init();
    //K->show(); b->show();

    for(int e = 0; e < num_elements; e++){
        cout << "\tAssembling for Element " << e+1 << "...\n\n";
        int index1 = M->get_element(e)->get_node1()->get_ID() - 1;
        int index2 = M->get_element(e)->get_node2()->get_ID() - 1;
        int index3 = M->get_element(e)->get_node3()->get_ID() - 1;
        int index4 = M->get_element(e)->get_node4()->get_ID() - 1;

        assembly_K(K, &Ks[e], index1, index2, index3, index4);
        assembly_b(b, &bs[e], index1, index2, index3, index4);
        //cout << "\t\t"; K->show(); cout << "\t\t"; b->show(); cout << "\n";
    }
}

void apply_neumann_boundary_conditions(Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_NEUMANN);

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_neumann_condition(c);
        
        int index = cond->get_node()->get_ID() - 1;
        b->add(cond->get_value(), index);
    }
    //cout << "\t\t"; b->show(); cout << "\n";
}

void add_column_to_RHS(Matrix* K, Vector* b, int col, float T_bar){
    for(int r = 0; r < K->get_nrows(); r++)
        b->add(-T_bar*K->get(r,col),r);
}

void apply_dirichlet_boundary_conditions(Matrix* K, Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_DIRICHLET);
    int previous_removed = 0;

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_dirichlet_condition(c);
        
        int index = cond->get_node()->get_ID() - 1 - previous_removed;
        float cond_value = cond->get_value();

        //K->show();
        K->remove_row(index);
        //K->show();
        //b->show();
        b->remove_row(index);
        //b->show();

        add_column_to_RHS(K, b, index, cond_value);
        //b->show();

        K->remove_column(index);
        //K->show();

        previous_removed++;
    }
}

void solve_system(Matrix* K, Vector* b, Vector* T, int mode){
    int n = K->get_nrows();
    
    Matrix Kinv(n,n);

    cout << "\tCalculating inverse of global matrix K...\n\n";
    if(mode == 1) calculate_inverse(K, n, &Kinv); //1
    else calculate_inverse_Cholesky(K, n, &Kinv); //2

    cout << "\tPerforming final calculation...\n\n";
    product_matrix_by_vector(&Kinv, b, n, n, T);
}

void merge_results_with_dirichlet(Vector* T, Vector* Tf, int n, Mesh* M){
    int num_dirichlet = M->get_quantity(NUM_DIRICHLET);

    int cont_dirichlet = 0;
    int cont_T = 0;
    for(int i = 0; i < n; i++){
        if(M->does_node_have_dirichlet_condition(i+1)){
            Condition* cond = M->get_dirichlet_condition(cont_dirichlet);
            cont_dirichlet++;
        
            float cond_value = cond->get_value();

            Tf->set(cond_value,i);
        }else{
            Tf->set(T->get(cont_T),i);
            cont_T++;
        }
    }
}
