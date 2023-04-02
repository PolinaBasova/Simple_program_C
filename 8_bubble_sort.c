#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void fill_array(int *adress_arr, int *pointer_size_arr){
    for (int i = 0; i < *pointer_size_arr; i++){
        *adress_arr = rand()%20 - 10; //Интервал от -10 до 10
        adress_arr ++;
    }
}

void print_array(int *adress_arr, int *pointer_size_arr){
    for (int i = 0; i < *pointer_size_arr; i++){
        printf("%d ", *adress_arr);
        adress_arr ++;
    }
}

int compare_for_sort_ascending(int *first_el, int *second_el){
    return (*first_el - *second_el);
}

int compare_for_sort_descending(int *first_el, int *second_el){
    return (*second_el - *first_el);
}

int compare_for_sort_abs_value(int *first_el, int *second_el){
    return (abs(*first_el) - abs(*second_el));
}

void swap(int *first_el, int *second_el){
    int buffer = *first_el;
    *first_el = *second_el;
    *second_el = buffer;
}

void bubble_sort(int *adress_arr, int *pointer_size_arr, int (*type_compare) (int*, int*)){
    int flag;
    do{
        flag = 0;
        for (int i = 0; i < *pointer_size_arr-1; i++){
            if (type_compare(adress_arr + i, adress_arr + i + 1) > 0){
                swap(adress_arr + i, adress_arr + i + 1);
                flag = 1;
            }
        }
    }while(flag!=0);
}

int main(){
    int *pointer_size_arr ;
    int *adress_arr;
    int size_of_arr; 
    pointer_size_arr = &size_of_arr;
    printf ("Input size of array: ");
    scanf("%d", &size_of_arr);
    adress_arr = (int*)malloc(size_of_arr * sizeof(int));
    fill_array(adress_arr, pointer_size_arr);
    printf("Unsorted array: ");
    print_array(adress_arr, pointer_size_arr);
    int (*type_compare) (int*, int*);
    printf("\nChoose sort type: \n1 - sort ascending \n2 - sort descending \n3 - sort by absolute value \nType: ");
    int type;
    scanf("%d", &type);
    if (type == 1){
        type_compare = &compare_for_sort_ascending;
    }
    if (type == 2){
        type_compare = &compare_for_sort_descending;
    }
    if (type == 3){
        type_compare = &compare_for_sort_abs_value;
    }
    bubble_sort(adress_arr, pointer_size_arr, type_compare);
    printf("Ascending sorted array: ");
    print_array(adress_arr, pointer_size_arr);
    free(adress_arr);
}