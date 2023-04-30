#include <stdio.h>
#include <string.h>

void replace_symb(char* buffer) {
    int i = 0;
    while (*(buffer + i) != '\0') {
        if (*(buffer + i) >= 65 && *(buffer + i) <= 90) {
            if (*(buffer + i - 2) != 33 && *(buffer + i - 2) != 46 && *(buffer + i - 2) != 63){
                *(buffer + i)+=32;
            }
        }
        i++;
    }
}

void delete_space(char* buffer) {
    int i = 0;
    int j = 0;
    while (*(buffer + i) != '\0') {
        if ((*(buffer + i) == 32) && ((*(buffer + i + 1) == 32)||(*(buffer + i + 1) == 46)||(*(buffer + i + 1) == 44))){
            j = i;
            while(*(buffer + j) != '\0') {
                *(buffer + j) = *(buffer + j + 1);
                j++;
            }
        }
        i++;
    }
}

void insert_space(char* buffer) {
    int i = 0;
    int j = 0;
    while (*(buffer + i) != '\0') {
        j = strlen(buffer) + 1;
        if (((*(buffer + i) == 33)||(*(buffer + i) == 44)||(*(buffer + i) == 46)||(*(buffer + i) == 58)||(*(buffer + i) == 59)||(*(buffer + i) == 63)) && ((*(buffer + i + 1) != 32))) {
            while (j != i){
                *(buffer + j + 1) = *(buffer + j);
                j--;
            }
            *(buffer + i + 1) = 32;
        }
        i++;
    }
}

void correct_string(char* buffer) {
    delete_space(buffer);
    insert_space(buffer);
    replace_symb(buffer);
}

int main() {
    FILE* fp = fopen("text.txt", "r");
    FILE* wp = fopen("correct_text.txt", "w");
    char buffer[250];
    while(fgets(buffer, 250, fp) != NULL){
        delete_space(buffer);
        insert_space(buffer);
        replace_symb(buffer);
        fputs(buffer, wp);
    }
    fclose(wp);
    fclose(fp);
}