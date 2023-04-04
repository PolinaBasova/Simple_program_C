#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void fill_array(int *arr, int size_arr){
    for (int i = 0; i < size_arr; i++){
        *arr = rand()%20 - 10; //Интервал от -10 до 10
        arr ++;
    }
}

void print_array(int *arr, int size_arr){
    for (int i = 0; i < size_arr; i++){
        printf("%d ", *arr);
        arr ++;
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

void bubble_sort(int *arr, int size_arr, int (*compare) (int*, int*)){
    int is_array_sorted_flag;
    do{
        is_array_sorted_flag = 0;
        for (int i = 0; i < size_arr-1; i++){
            if (compare(arr + i, arr + i + 1) > 0){
                swap(arr + i, arr + i + 1);
                is_array_sorted_flag = 1;
            }
        }
    }while(is_array_sorted_flag!=0);
}

int main(){
    int *arr;
    int size_arr; 
    printf ("Input size of array: ");
    scanf("%d", &size_arr);
    arr = (int*)malloc(size_arr * sizeof(int));
    fill_array(arr, size_arr);
    printf("Unsorted array: ");
    print_array(arr, size_arr);
    int (*compare) (int*, int*);
    printf("\nChoose sort type: \n1 - sort ascending \n2 - sort descending \n3 - sort by absolute value \nType: ");
    int type;
    scanf("%d", &type);
    if (type == 1){
        compare = &compare_for_sort_ascending;
    }
    if (type == 2){
        compare = &compare_for_sort_descending;
    }
    if (type == 3){
        compare = &compare_for_sort_abs_value;
    }
    bubble_sort(arr, size_arr, compare);
    printf("Ascending sorted array: ");
    print_array(arr, size_arr);
    free(arr);
}