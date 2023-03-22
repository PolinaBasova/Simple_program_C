#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size_of_arr 10

void print_array(int *adress_arr){
    for (int i = 0; i < size_of_arr; i++){
        *adress_arr = rand()%10;
        printf("%d ", *adress_arr);
        adress_arr ++;
    }
}

int search_max (int *adress_arr){
    int Max = 0;
    for (int i = 0; i < size_of_arr; i++){
        if ( *adress_arr >= Max){
            Max = *adress_arr;
        }
        adress_arr ++;
    }
    return (Max);
}

int search_min (int *adress_arr){
    int Min = *adress_arr;
    for (int i = 0; i < size_of_arr; i++){
        if ( *adress_arr <= Min){
            Min = *adress_arr;
        }
        adress_arr ++;
    }
    return (Min);
}

float calc_mean (int *adress_arr){
    double sum = 0;
    for (int i = 0; i < size_of_arr; i++){
        sum += *adress_arr;
        adress_arr ++;
    }
    return (sum/(size_of_arr - 1));
}

float calc_RMS (int *adress_arr){
    double sum_squared_differences = 0;
    for (int i = 0; i < size_of_arr; i++){
        sum_squared_differences += pow((*adress_arr - calc_mean(adress_arr)), 2);
    }
    return (sqrtl(sum_squared_differences/(size_of_arr-1)));
}

int main(){
    int arr[size_of_arr];
    print_array (&arr[0]);
    printf("\n Max = %d", search_max (&arr[0]));
    printf("\n Min = %d", search_min (&arr[0]));
    printf("\n Mean = %f", calc_mean(&arr[0]));
    printf("\n RMS = %f", calc_RMS(&arr[0]));
}