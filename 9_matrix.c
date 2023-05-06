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

void print_matrix(Matrix* data){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%f\t", data->arr[i][j]);
        }
        printf("\n");
    }
}

void sum_matrices(Matrix* sum_point, Matrix* point_A, Matrix* point_B){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            sum_point->arr[i][j] = (point_A->arr[i][j]) + (point_B->arr[i][j]);
        }
    }
}

void multiplication_matrices(Matrix* mult_point, Matrix* point_A, Matrix* point_B){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            mult_point->arr[i][j] = 0;
            for (int s = 0; s < 3; s++){
                mult_point->arr[i][j] += (point_A->arr[i][s]) * (point_B->arr[s][j]);
            }
        }
    }
}

float calc_det(Matrix* point){
    float det = 0;
    int num_el = 0;  // создаем массив для элементов алг. дополнений
    float *data = (float*)malloc(4 * sizeof(float));
    for (int line_det = 0; line_det < 3; line_det++){
        for (int line_alg = 0; line_alg < 3; line_alg++){
            for (int column_alg = 1; column_alg < 3; column_alg++){
                if (line_alg!=line_det){
                    *(data + num_el) = point->arr[line_alg][column_alg];
                    num_el++;
                }
            }
        }
        num_el = 0;
        det+=pow(-1, line_det)*(point->arr[line_det][0])*((*data) * (*(data+3)) - (*(data+1)) * (*(data+2)));
    }
    free(data);
    return(det);
}

void transpose_matrix(Matrix* transp_point, Matrix* point){
    for(int line = 0; line < 3; line++){
        for(int column = 0; column < 3; column++){
            transp_point->arr[line][column] = point->arr[column][line];
        }
    }
}

void inverse_matrix(Matrix* inv_point, Matrix* point){
    int num_el = 0;  // создаем массив для элементов алг. дополнений
    float *data = (float*)malloc(4 * sizeof(float));
    for (int line_inv = 0; line_inv < 3; line_inv++){
        for (int column_inv = 0; column_inv < 3; column_inv++){
            for (int line_alg = 0; line_alg < 3; line_alg++){
                for (int column_alg = 0; column_alg < 3; column_alg++){
                    if ((line_alg!=line_inv)&&(column_alg!=column_inv)){
                        *(data + num_el) = point->arr[line_alg][column_alg];
                        num_el++;
                    }
                }
            }
            num_el = 0;
            inv_point->arr[line_inv][column_inv] = pow(-1, line_inv+column_inv)*((*data) * (*(data+3)) - (*(data+1)) * (*(data+2)))/calc_det(point);
        }
    }
    free(data);
    Matrix transp;
    transpose_matrix(&transp, inv_point);
}

void define_from_file(char file_name[11], Matrix* read_matrix){
    FILE* file = fopen(file_name, "r");
    for (int line = 0; line < 3; line++){
        for (int column = 0; column < 3; column++){
            fscanf(file, "%f", &read_matrix->arr[line][column]);
        }
    }
    fclose(file);
}

void write_to_file(char file_name[9], Matrix* write_matrix){
    FILE* file = fopen(file_name, "w");
    for (int line = 0; line < 3; line++){
        for (int column = 0; column < 3; column++){
            fprintf(file, "%f ", write_matrix->arr[line][column]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

//Запись в бинарный файл 
//Т.е. не преобразует числа в символьный тип данных, а записывает их двоичное представление
void write_to_bin_file(char file_name[9], Matrix* write_matrix){  
    FILE* file = fopen(file_name, "wb");
    for (int line = 0; line < 3; line++){
        for (int column = 0; column < 3; column++){
            fwrite(&write_matrix->arr[line][column], sizeof(float), 1, file);
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
        define_from_file("file_A.txt", &A);
        define_from_file("file_B.txt", &B);
    }
    
    printf("Matrix А: \n");
    print_matrix(&A);
    
    printf("Matrix B: \n");
    print_matrix(&B);
    
    printf("Matrix А+B: \n");
    Matrix sum;
    sum_matrices(&sum, &A, &B);
    print_matrix(&sum);
    
    printf("Matrix А*B: \n");
    Matrix mult;
    multiplication_matrices(&mult, &A, &B);
    print_matrix(&mult);
    
    printf("det A: %f \n", calc_det(&A));
    printf("det В: %f \n", calc_det(&B));
    
    printf("Inverse matrix А: \n");
    Matrix inv;
    inverse_matrix(&inv, &A);
    print_matrix(&inv);
    
    write_to_file("file.txt", &inv); //Записываем в файл обратную матрицу
    write_to_bin_file("file.bin", &inv);
}