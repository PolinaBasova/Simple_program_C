#include <stdio.h>
#include <math.h>

double dx = 0, x0 = 0, x = 0;

double Func( double x0 ){
    return (x0*x0-4*x0+3);
}

double dFunc( double x0){
    return ((Func(x0+dx)-Func(x0))/dx);
}

double d2Func( double x0){
    return ((dFunc(x0+dx)-dFunc(x0))/dx);
}

int main() {
    dx = pow(0.1, 5);
    double Max, Min;
    int Prec;
    printf("Input approximation: Max = ");
    scanf("%lf", &Max);
    printf("Min = ");
    scanf("%lf", &Min);
    printf("Input a precision: Prec = ");
    scanf("%d", &Prec);
    if (Func(Max)*d2Func(Max) > 0){
        x0=Max;
    }
    else{
        x0=Min;
    }
    x=x0-(Func(x0)/dFunc(x0));
    while (  fabs(x - x0) >= pow(0.1, Prec) ){
        x0=x;
        x=x0-(Func(x0)/dFunc(x0));
    }
    printf("%.*f\n", Prec, x);
}
