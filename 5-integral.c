#include <stdio.h>
#include <math.h>

double Func1(double x){
    return (pow(x, 2));
}

double Func2(double x){
    return (pow(x, 3));
}

double dFunc(double (*Funcion) (double), double x, double dx){
    return ((Funcion(x+dx)-Funcion(x))/dx);
}

double d2Func(double (*Funcion) (double), double x, double dx){
    return ((dFunc(Funcion, x+dx, dx)-dFunc(Funcion, x, dx))/dx);
}

/*
Ищет максимум второй производной, вычисляет ошибку
*/
double calc_error(double (*Funcion) (double), double Up, double Down, int Num, double dx){
    double len_of_interval = Up - Down;
    double Max = 0;
    int j;
    for (j = 1; j <= Num; j++){
        if (fabs(d2Func(Funcion, Down, dx))>= Max){
            Max = fabs(d2Func(Funcion, Down, dx));
        }
        Down += dx;
    }
    return ((len_of_interval*Max*dx*dx)/12);
}

double calc_integral(double (*Funcion) (double), double Up, double Down, int Num, double dx){
    double Sum = ((Funcion(Up) + Funcion(Down))*dx)/2;
    int i;
    for (i = 1; i <= Num; i++){
        Sum += Funcion(Down)*dx;
        Down += dx;
    }
    return(Sum);
}

int main() {
    double Up, Down;
    int Num;
    printf("Input limits: Up = ");
    scanf("%lf", &Up);
    printf("Down = ");
    scanf("%lf", &Down);
    printf("Input a number of partitions: Num = ");
    scanf("%d", &Num);
    double dx = (Up - Down)/Num;
    double (*Funcion) (double);
    Funcion = &Func1;
    printf("%.10lf\n", calc_integral(Funcion, Up, Down, Num, dx));
    printf("%.10lf\n", calc_error(Funcion, Up, Down, Num, dx));
}