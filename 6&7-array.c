#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void print_array(int *adress_arr, int *pointer_size_arr){
    printf("Array: ");
    for (int i = 0; i < *pointer_size_arr; i++){
        *adress_arr = rand()%10;
        printf("%d ", *adress_arr);
        adress_arr ++;
    }
}

int search_max (int *adress_arr, int *pointer_size_arr){
    int Max = 0;
    for (int i = 0; i < *pointer_size_arr; i++){
        if ( *adress_arr >= Max){
            Max = *adress_arr;
        }
        adress_arr ++;
    }
    return (Max);
}

int search_min (int *adress_arr, int *pointer_size_arr){
    int Min = *adress_arr;
    for (int i = 0; i < *pointer_size_arr; i++){
        if ( *adress_arr <= Min){
            Min = *adress_arr;
        }
        adress_arr ++;
    }
    return (Min);
}

float calc_mean (int *adress_arr, int *pointer_size_arr){
    double sum = 0;
    for (int i = 0; i < *pointer_size_arr; i++){
        sum += *adress_arr;
        adress_arr ++;
    }
    return (sum/(*pointer_size_arr - 1));
}

float calc_RMS (int *adress_arr, int *pointer_size_arr){
    double sum_squared_differences = 0;
    for (int i = 0; i < *pointer_size_arr; i++){
        sum_squared_differences += pow((*adress_arr - calc_mean(adress_arr, pointer_size_arr)), 2);
    }
    return (sqrtl(sum_squared_differences/(*pointer_size_arr-1)));
}

int main(){
    int *pointer_size_arr ;
    int *adress_arr;
    int size_of_arr; 
    pointer_size_arr = &size_of_arr;
    
    printf ("Input size of static array: ");
    scanf("%d", &size_of_arr);
    int arr[size_of_arr];
    adress_arr = &arr[0];
    
    print_array (adress_arr, pointer_size_arr);
    printf("\nMax = %d", search_max (adress_arr, pointer_size_arr));
    printf("\nMin = %d", search_min (adress_arr, pointer_size_arr));
    printf("\nMean = %f", calc_mean(adress_arr, pointer_size_arr));
    printf("\nRMS = %f", calc_RMS(adress_arr, pointer_size_arr));
    
    printf ("\nInput size of dynamic array: ");
    scanf("%d", &size_of_arr);
    adress_arr = (int*)malloc(size_of_arr * sizeof(int));
    
    print_array (adress_arr, pointer_size_arr);
    printf("\nMax = %d", search_max (adress_arr, pointer_size_arr));
    printf("\nMin = %d", search_min (adress_arr, pointer_size_arr));
    printf("\nMean = %f", calc_mean(adress_arr, pointer_size_arr));
    printf("\nRMS = %f", calc_RMS(adress_arr, pointer_size_arr));
    
    free(adress_arr);
}