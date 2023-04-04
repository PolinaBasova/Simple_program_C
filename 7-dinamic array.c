#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void fill_array(int *arr, int size_arr){
    for (int i = 0; i < size_arr; i++){
        *arr = rand()%10; 
        arr ++;
    }
}

void print_array(int *arr, int size_arr){
    for (int i = 0; i < size_arr; i++){
        printf("%d ", *arr);
        arr ++;
    }
}

int search_max (int *arr, int size_arr){
    int Max = 0;
    for (int i = 0; i < size_arr; i++){
        if ( *arr >= Max){
            Max = *arr;
        }
        arr ++;
    }
    return (Max);
}

int search_min (int *arr, int size_arr){
    int Min = *arr;
    for (int i = 0; i < size_arr; i++){
        if ( *arr <= Min){
            Min = *arr;
        }
        arr ++;
    }
    return (Min);
}

float calc_mean (int *arr, int size_arr){
    double sum = 0;
    for (int i = 0; i < size_arr; i++){
        sum += *arr;
        arr ++;
    }
    return (sum/(size_arr - 1));
}

float calc_RMS (int *arr, int size_arr){
    double sum_squared_differences = 0;
    for (int i = 0; i < size_arr; i++){
        sum_squared_differences += pow((*arr - calc_mean(arr, size_arr)), 2);
    }
    return (sqrtl(sum_squared_differences/(size_arr-1)));
}

int main(){
    int size_arr; 
    printf ("Input size of dynamic array: ");
    scanf("%d", &size_arr);
    int *arr = (int*)malloc(size_arr * sizeof(int));
    fill_array (arr, size_arr);
    print_array (arr, size_arr);
    printf("\nMax = %d", search_max (arr, size_arr));
    printf("\nMin = %d", search_min (arr, size_arr));
    printf("\nMean = %f", calc_mean(arr, size_arr));
    printf("\nRMS = %f", calc_RMS(arr, size_arr));
    free(arr);
}