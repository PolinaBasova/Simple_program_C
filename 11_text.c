#include <stdio.h>
#include <string.h>
#include <ctype.h>

void make_capital(char* buffer) {
    int i = 0;
    while (*(buffer + i) != '\0') {
        if (*(buffer + i - 2) == '!' || *(buffer + i - 2) == '.' || *(buffer + i - 2) == '?') {
            if (*(buffer + i) >= 'a' && *(buffer + i) <= 'z'){
                *(buffer + i) = toupper(*(buffer + i));
            }
        }
        i++;
    }
    if (*buffer >= 'a' && *buffer <= 'z'){
        *buffer = toupper(*buffer);
    }
}

void make_small(char* buffer) {
    int i = 0;
    while (*(buffer + i) != '\0') {
        if (*(buffer + i - 2) != '!' && *(buffer + i - 2) != '.' && *(buffer + i - 2) != '?'){
            if (*(buffer + i) >= 'A' && *(buffer + i) <= 'Z') {
                *(buffer + i) = tolower(*(buffer + i));
            }
        }
        i++;
    }
}

void replace_symb(char* buffer) {
    int i = 0;
    while (*(buffer + i) != '\0') {
        if (*(buffer + i - 2) != '!' && *(buffer + i - 2) != '.' && *(buffer + i - 2) != '?'){
            if (*(buffer + i) >= 'A' && *(buffer + i) <= 'Z') {
                *(buffer + i) = tolower(*(buffer + i));
            }
        }
        else {
            if (*(buffer + i) >= 'a' && *(buffer + i) <= 'z'){
                *(buffer + i) = toupper(*(buffer + i));
            }
        }
        i++;
    }
    if (*buffer >= 'a' && *buffer <= 'z'){
        *buffer = toupper(*buffer);
    }
}

void delete_space(char* buffer) {
    int i = 0;
    int j = 0;
    while (*(buffer + i) != '\0') {
        if (*buffer == ' '){
            j = 0;
            while(*(buffer + j) != '\0') {
                *(buffer + j) = *(buffer + j + 1);
                j++;
            }
        }
        if (*(buffer + i) == ' '){
            while (*(buffer + i + 1) == ' ') {
                j = i;
                while(*(buffer + j) != '\0') {
                    *(buffer + j) = *(buffer + j + 1);
                    j++;
                } 
            }
        }
        if ((*(buffer + i) == ' ') && ((*(buffer + i + 1) == '.')||(*(buffer + i + 1) == ','))){
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
        if (((*(buffer + i) == '!')||(*(buffer + i) == ',')||(*(buffer + i) == '.')||(*(buffer + i) == ':')||(*(buffer + i) == ';')||(*(buffer + i) == '?')) && ((*(buffer + i + 1) != ' '))) {
            while (j != i){
                *(buffer + j + 1) = *(buffer + j);
                j--;
            }
            *(buffer + i + 1) = ' ';
        }
        i++;
    }
}

int main() {
    FILE* fp = fopen("text.txt", "r");
    FILE* wp = fopen("correct_text.txt", "w");
    char buffer[200];
    while(fgets(buffer, 200, fp) != NULL){
        delete_space(buffer);
        insert_space(buffer);
        make_small(buffer);
        make_capital(buffer);
        fputs(buffer, wp);
    }
    fclose(wp);
    fclose(fp);
}