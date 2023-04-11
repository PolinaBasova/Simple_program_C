#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float arr[3][3];
} Matrix;

void fill_matrix(Matrix* point){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            point->arr[i][j] = rand()%10;
        }
    }
}

void print_matrix(Matrix any_matrix){
    Matrix *point;
    point = &any_matrix;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%f\t", point->arr[i][j]);
        }
        printf("\n");
    }
}

Matrix sum_matrices(Matrix* point_A, Matrix* point_B){
    Matrix sum;
    Matrix* point_sum;
    point_sum = &sum;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            point_sum->arr[i][j] = (point_A->arr[i][j]) + (point_B->arr[i][j]);
        }
    }
    return (sum);
}

Matrix multiplication_matrices(Matrix* point_A, Matrix* point_B){
    Matrix mult;
    Matrix* point_mult;
    point_mult = &mult;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            point_mult->arr[i][j] = 0;
            for (int s = 0; s < 3; s++){
                point_mult->arr[i][j] += (point_A->arr[i][s]) * (point_B->arr[s][j]);
            }
        }
    }
    return (mult);
}

float calc_det(Matrix* point){
    float det = 0;
    int num_el = 0;  // создаем массив для элементов алг. дополнений
    float *data = (float*)malloc(4 * sizeof(float));
    for (int i = 0; i < 3; i++){
        for (int s = 0; s < 3; s++){
            for (int k = 1; k < 3; k++){
                if (s!=i){
                    *(data + num_el) = point->arr[s][k];
                    num_el++;
                }
            }
        }
        num_el = 0;
        det+=pow(-1, i)*(point->arr[i][0])*((*data) * (*(data+3)) - (*(data+1)) * (*(data+2)));
    }
    free(data);
    return(det);
}

Matrix transpose_matrix(Matrix* point){
    Matrix transp;
    Matrix* point_transp;
    point_transp = &transp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            point_transp->arr[i][j] = point->arr[j][i];
        }
    }
    return(transp);
}

Matrix inverse_matrix(Matrix* point){
    Matrix inv;
    Matrix* point_inv;
    point_inv = &inv;
    int num_el = 0;  // создаем массив для элементов алг. дополнений
    float *data = (float*)malloc(4 * sizeof(float));
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int s = 0; s < 3; s++){
                for (int k = 0; k < 3; k++){
                    if ((s!=i)&&(k!=j)){
                        *(data + num_el) = point->arr[s][k];
                        num_el++;
                    }
                }
            }
            num_el = 0;
            point_inv->arr[i][j] = pow(-1, i+j)*((*data) * (*(data+3)) - (*(data+1)) * (*(data+2)))/calc_det(point);
        }
    }
    free(data);
    return(transpose_matrix(point_inv));
}

void define_from_file(FILE* file, Matrix* point_read_matrix){
    file = fopen("file.txt", "r");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fscanf(file, "%f", point_read_matrix->arr[i][j]);
        }
    }
    fclose(file);
}

Matrix write_to_file(FILE* file, Matrix W){
    Matrix* point_read_matrix;
    point_read_matrix = &W;
    file = fopen("file.txt", "w");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fprintf(file, "%f", point_read_matrix->arr[i][j]);
        }
    }
    fclose(file);
}

int main(){
    Matrix A;
    Matrix B;
    int method;
    printf("How do you want to define the matrix?\n 1 - random \n 2 - from file \n");
    scanf("%d", &method);
    if (method==1){
        fill_matrix(&A);
        fill_matrix(&B);
    }
    else{
        FILE* file;
        define_from_file(file, &A);
    }
    
    printf("Matrix А: \n");
    print_matrix(A);
    
    printf("Matrix B: \n");
    print_matrix(B);
    
    printf("Matrix А+B: \n");
    print_matrix(sum_matrices(&A, &B));
    
    printf("Matrix А*B: \n");
    print_matrix(multiplication_matrices(&A, &B));
    
    printf("det A: %f \n", calc_det(&A));
    printf("det В: %f \n", calc_det(&B));
    
    printf("Inverse matrix А: \n");
    print_matrix(inverse_matrix(&A));
    
    FILE* file_record;
    write_to_file(file_record, inverse_matrix(&A)); //Например, записываем в файл обратную матрицу
}