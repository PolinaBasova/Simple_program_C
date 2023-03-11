#include <stdio.h>
#include <math.h>

double Func(double x0){
    return (x0*x0 - 1);
}

double dFunc(double x0, double dx){
    return ((Func(x0 + dx) - Func(x0))/dx);
}

double resolve_question(double x0, double Prec){
    double dx = 1.e-5;
    double x = x0 - (Func(x0)/dFunc(x0, dx));
    while (fabs(x - x0) >= pow(0.1, Prec)){
        x0 = x;
        x = x0 - (Func(x0)/dFunc(x0, dx));
        printf("%f\n", x);
    }
    return (x);
}

int main() {
    double x0;
    int Prec;
    printf("Input approximation: ");
    scanf("%lf", &x0);
    printf("Input a precision: Prec = ");
    scanf("%d", &Prec);
    printf("%.*f\n", Prec, resolve_question(x0, Prec));
}
