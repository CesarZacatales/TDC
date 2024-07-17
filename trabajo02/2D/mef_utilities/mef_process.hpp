/*float calculate_local_area(float x1, float y1, float x2, float y2, float x3, float y3){
    float A = abs((x1*y2 + x2*y3 + x3*y1) - (x1*y3 + x2*y1 + x3*y2))/2;
    return ((A==0)?0.000001:A);
} */

float calculate_local_jacobian(float x1, float y1, float x2, float y2, float x3, float y3){
    float J = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
    return ((J==0)?0.000001:J);
}

void calculate_B(Matrix* B){
    B->set(-1,0,0);  B->set(1,0,1);  B->set(0,0,2);
    B->set(-1,1,0);  B->set(0,1,1);  B->set(1,1,2);
}

void calculate_local_A(Matrix* A, float x1, float y1, float x2, float y2, float x3, float y3){
    A->set(y3-y1, 0, 0);   A->set(x1-x3, 0, 1);
    A->set(y1-y2, 1, 0);   A->set(x2-x1, 1, 1);
}

void create_local_K(Matrix* K, int element_id, Mesh* M){
    K->set_size(3,3);

    //float k = M->get_problem_data(THERMAL_CONDUCTIVITY);
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate();
    //float Area = calculate_local_area(x1, y1, x2, y2, x3, y3);
    float J = calculate_local_jacobian(x1, y1, x2, y2, x3, y3);

    Matrix B(2,3), A(2,2);
    calculate_B(&B);
    calculate_local_A(&A, x1, y1, x2, y2, x3, y3);
    //B.show(); A.show();

    Matrix Bt(3,2), At(2,2);
    transpose(&B,2,3,&Bt);
    transpose(&A,2,2,&At);
    //Bt.show(); At.show();

    Matrix res1, res2, res3;
    product_matrix_by_matrix(&A,&B,&res1);
    product_matrix_by_matrix(&At,&res1,&res2);
    product_matrix_by_matrix(&Bt,&res2,&res3);
    product_scalar_by_matrix(1/(420*J*J),&res3,3,3,K);

    //cout << "\t\tLocal matrix created for Element " << element_id+1 << ": "; K->show(); cout << "\n";
}

void create_local_b(Vector* b, int element_id, Mesh* M){
    b->set_size(3);

    //float Q = M->get_problem_data(HEAT_SOURCE);
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate();
    float J = calculate_local_jacobian(x1, y1, x2, y2, x3, y3);

    b->set(J*(1/20),0);
    b->set(J*(3/40),1);
    b->set(J*(1/120),2);

    //cout << "\t\tLocal vector created for Element " << element_id+1 << ": "; b->show(); cout << "\n";
}

void create_local_systems(Matrix* Ks, Vector* bs, int num_elements, Mesh* M){
    for(int e = 0; e < num_elements; e++){
        cout << "\tCreating local system for Element " << e+1 << "...\n\n";
        create_local_K(&Ks[e],e,M);
        create_local_b(&bs[e],e,M);
    }
}

void assembly_K(Matrix* K, Matrix* local_K, int index1, int index2, int index3){
    K->add(local_K->get(0,0),index1,index1);    K->add(local_K->get(0,1),index1,index2);    K->add(local_K->get(0,2),index1,index3);
    K->add(local_K->get(1,0),index2,index1);    K->add(local_K->get(1,1),index2,index2);    K->add(local_K->get(1,2),index2,index3);
    K->add(local_K->get(2,0),index3,index1);    K->add(local_K->get(2,1),index3,index2);    K->add(local_K->get(2,2),index3,index3);
}

void assembly_b(Vector* b, Vector* local_b, int index1, int index2, int index3){
    b->add(local_b->get(0),index1);
    b->add(local_b->get(1),index2);
    b->add(local_b->get(2),index3);
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

        assembly_K(K, &Ks[e], index1, index2, index3);
        assembly_b(b, &bs[e], index1, index2, index3);
        //cout << "\t\t"; K->show(); cout << "\t\t"; b->show(); cout << "\n";
    }
}

void apply_boundary_conditions_2(Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_CONDITION_2);

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_condition_2(c);
        
        int index = cond->get_node()->get_ID() - 1;
        b->add(cond->get_value(), index);
    }
    //cout << "\t\t"; b->show(); cout << "\n";
}

void add_column_to_RHS(Matrix* K, Vector* b, int col, float P_bar){
    for(int r = 0; r < K->get_nrows(); r++)
        b->add(-P_bar*K->get(r,col),r);
}

void apply_boundary_conditions_1(Matrix* K, Vector* b, Mesh* M){
    int num_conditions = M->get_quantity(NUM_CONDITION_1);
    int previous_removed = 0;

    for(int c = 0; c < num_conditions; c++){
        Condition* cond = M->get_condition_1(c);
        
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

void solve_system(Matrix* K, Vector* b, Vector* P, int mode){
    int n = K->get_nrows();
    
    Matrix Kinv(n,n);

    cout << "\tCalculating inverse of global matrix K...\n\n";
    if(mode == 1) calculate_inverse(K, n, &Kinv); //1
    else calculate_inverse_Cholesky(K, n, &Kinv); //2

    cout << "\tPerforming final calculation...\n\n";
    product_matrix_by_vector(&Kinv, b, n, n, P);
}

void merge_results_with_condition_1(Vector* P, Vector* Pf, int n, Mesh* M){
    int num_condition_1 = M->get_quantity(NUM_CONDITION_1);

    int cont_condition_1 = 0;
    int cont_P = 0;
    for(int i = 0; i < n; i++){
        if(M->does_node_have_condition_1(i+1)){
            Condition* cond = M->get_condition_1(cont_condition_1);
            cont_condition_1++;
        
            float cond_value = cond->get_value();

            Pf->set(cond_value,i);
        }else{
            Pf->set(P->get(cont_P),i);
            cont_P++;
        }
    }
}
