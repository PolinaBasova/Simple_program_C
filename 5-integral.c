#include <stdio.h>
#include <math.h>

double dx = 0, x = 0;

double Func( double x ){
    return (-x*x+4);
}

double dFunc( double x){
    return ((Func(x+dx)-Func(x))/dx);
}

double d2Func( double x){
    return ((dFunc(x+dx)-dFunc(x))/dx);
}

int main() {
    double Up, Down, Integral;
    int N, i;
    printf("Input limits: Up = ");
    scanf("%lf", &Up);
    printf("Down = ");
    scanf("%lf", &Down);
    printf("Input a number of partitions: N = ");
    scanf("%d", &N);
    dx = (Up-Down)/N;
    x=dx/2;
    for (i=2; i<=N; i++){
        x+=dx;
        Integral+=Func(x)*dx;
    }
    printf("%lf", Integral);
}