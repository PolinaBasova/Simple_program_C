#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int num_lines;
    int num_columns;
    float *arr;
} Matrix;

Matrix* create_matrix(int row_number, int col_number) {
    Matrix* m;
    m = (Matrix*)malloc(sizeof(Matrix));
    m->num_lines = row_number;
    m->num_columns = col_number;
    m->arr = (float*)malloc(row_number * col_number * sizeof(float));
    return m;
}

void destroy_matrix(Matrix* m) {
    free(m->arr);
}

float* element(Matrix* m, int i, int j) {
    return((m->arr)+i*(m->num_columns)+j);
}

void fill_matrix(Matrix* m) {
    for (int i = 0; i < (m->num_lines); i++) {
        for (int j = 0; j < (m->num_columns); j++) {
            *element(m, i, j) = rand()%10;
        }
    }
}

void print_matrix(Matrix* m) {
    for (int i = 0; i < (m->num_lines); i++) {
        for (int j = 0; j < (m->num_columns); j++) {
            printf("%f\t", *element(m, i, j));
        }
        printf("\n");
    }
    
}

Matrix* sum_matrices(Matrix* A, Matrix* B) {
    Matrix* sum = create_matrix(A->num_lines, A->num_columns);
    for (int i = 0; i < (sum->num_lines); i++) {
        for (int j = 0; j < (sum->num_columns); j++) {
            *element(sum, i, j) = *element(A, i, j) + *element(B, i, j);
        }
    }
    return(sum);
}

Matrix* multiplication_matrices(Matrix* A, Matrix* B) {
    Matrix* mult = create_matrix(A->num_lines, B->num_columns); 
    for (int s = 0; s < (mult->num_columns); s++) { 
        for (int i = 0; i < (mult->num_lines); i++) {
            *((mult->arr) + s*(mult->num_columns) + i) = 0;
            for (int j = 0; j < (A->num_columns); j++) {
                *element(mult, s, i) += (*element(A, s, j)) * (*element(B, j, i));
            }
        }
    }
    return(mult);
}

void fill_matrix_alg_addition (Matrix* new_matr, Matrix* M, int line, int column){ 
    int flag_row = 0;
    int flag_column = 0;
    for (int i = 0; i < M->num_lines - 1; i++){
        if (i==line){
            flag_row = 1;
        }
        flag_column = 0;
        for (int j = 0; j < M->num_lines - 1; j++){
            if(j == column){
                flag_column = 1;
            }
            *element(new_matr, i, j) =  *element(M, i+flag_row, j+flag_column);
        }
    }
}

float calc_det(Matrix* M){ 
    float det = 0;
    int sign = 1;
    if (M->num_lines == 1) {
        return (*(element(M, 0, 0)));
    }
    if (M->num_lines == 2) {
        return ((*element(M, 0, 0))*(*element(M, 0, 3)) - (*element(M, 0, 1))*(*element(M, 0, 2)));
    }
    else {
        Matrix* new_matr = create_matrix(M->num_lines-1, M->num_lines-1);
        for (int j = 0; j < M->num_lines; j++) {
            fill_matrix_alg_addition(new_matr, M, 0, j);
            det += sign*(*(M->arr + j))*calc_det(new_matr);
            sign = -sign;
        }
        destroy_matrix(new_matr);
    }
    return(det);
}

Matrix* inverse_matrix(Matrix* M) {
    Matrix* inv = create_matrix(M->num_lines, M->num_columns);
    int sign = 1;
    for (int i=0; i < inv-> num_columns; i++) {
        for (int j=0; j < inv-> num_columns; j++) {
            Matrix* alg_add = create_matrix(M->num_lines - 1, M->num_columns - 1);
            fill_matrix_alg_addition(alg_add, M, i, j);
            //printf("matrix alg add \n");
            //print_matrix(alg_add);
            //printf("det alg add: %f \n", calc_det(alg_add));
            *element(inv, j, i) =(sign*calc_det(alg_add))/calc_det(M);
            sign = -sign;
        }
    }
    return(inv);
}

Matrix* transpose_matrix(Matrix* M) {
    Matrix* transp = create_matrix(M->num_lines, M->num_columns);
    
    return(transp);
}

void test_det_2x2() {
    Matrix* A = create_matrix(2, 2);
    fill_matrix(A);
    print_matrix(A);
    float det = calc_det(A);
    printf("det = %f\n", det);
}

void test_det_3x3() {
    Matrix* A = create_matrix(3, 3);
    fill_matrix(A);
    print_matrix(A);
    float det = calc_det(A);
    printf("det = %f\n", det);
}

void test_det_4x4() {
    Matrix* A = create_matrix(4, 4);
    fill_matrix(A);
    print_matrix(A);
    float det = calc_det(A);
    printf("det = %f\n", det);
}

void test_inverse_matrix() {
    Matrix* A = create_matrix(2, 2);
    fill_matrix(A);
    print_matrix(A);
    float det = calc_det(A);
    printf("det = %f\n", det);
    print_matrix(inverse_matrix(A));
}

void define_from_file(char file_name[11], Matrix* M){
    FILE* file = fopen(file_name, "r");
    for (int i = 0; i < M->num_lines; i++){
        for (int j = 0; j < M->num_columns; j++){
            fscanf(file, "%f", element(M, i, j));
        }
    }
    fclose(file);
}

void write_to_file(char file_name[11], Matrix* M){
    FILE* file = fopen(file_name, "w");
    for (int i = 0; i < M->num_lines; i++){
        for (int j = 0; j < M->num_columns; j++){
            fprintf(file, "%f ", *element(M, i, j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(){
    //test_det_2x2();
    //test_det_3x3();
    //test_det_4x4();
    //test_inverse_matrix();
    //exit(1);
    
    int num_lines_A, num_columns_A;
    printf("Enter the numbers of lines of first matrix? ");
    scanf("%d", &num_lines_A);
    printf("Enter the numbers of columns of first matrix? ");
    scanf("%d", &num_columns_A);
    Matrix* A = create_matrix(num_lines_A, num_columns_A);
  
    int num_lines_B, num_columns_B;
    printf("Enter the numbers of lines of second matrix? ");
    scanf("%d", &num_lines_B);
    printf("Enter the numbers of columns of second matrix? ");
    scanf("%d", &num_columns_B);
    Matrix* B = create_matrix(num_lines_B, num_columns_B);
    
    int method;
    printf("How do you want to define the matrices?\n 1 - random \n 2 - from file \n");
    scanf("%d", &method);
    if (method==1){
        fill_matrix(A);
        fill_matrix(B);
    }
    else{
        define_from_file("file_A.txt", A);
        define_from_file("file_B.txt", B);
    }
    
    printf("Matrix А: \n");
    print_matrix(A);
    
    printf("Matrix B: \n");
    print_matrix(B);
    
    printf("Matrix А+B: \n");
    print_matrix(sum_matrices(A, B));
    destroy_matrix(sum_matrices(A, B));
    
    printf("Matrix А*B: \n");
    print_matrix(multiplication_matrices(A, B));
    destroy_matrix(multiplication_matrices(A, B));

    printf("det A: %f \n", calc_det(A));
    printf("det В: %f \n", calc_det(B));
    
    printf("Inverse matrix А: \n");
    print_matrix(inverse_matrix(A));
    write_to_file("results.txt", inverse_matrix(A));
    destroy_matrix(inverse_matrix(A));
   
    destroy_matrix(A);
    destroy_matrix(B);
}