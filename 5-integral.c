#include <stdio.h>
#include <math.h>

double Func(double x){
    return (pow(x, 2));
}

double dFunc(double x, double dx){
    return ((Func(x+dx)-Func(x))/dx);
}

double d2Func(double x, double dx){
    return ((dFunc(x+dx, dx)-dFunc(x, dx))/dx);
}

double error(double Up, double Down, int Num, double dx){
    double x2 = Down;
    double Max = 0;
    int j;
    for (j = 1; j <= Num; j++){
        if (fabs(d2Func(x2, dx))>= Max){
            Max = fabs(d2Func(x2, dx));
        }
        x2 += dx;
    }
    return (((Up-Down)*Max*dx*dx)/12);
}

double calc_integral(double Up, double Down, int Num, double dx){
    double x1 = Down;
    double Sum = 0;
    int i;
    for (i = 1; i <= Num; i++){
        Sum += Func(x1)*dx;
        x1 += dx;
    }
    Sum += ((Func(Up) + Func(Down))*dx)/2;
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
    printf("%.10lf\n", calc_integral(Up, Down, Num, dx));
    printf("%.10lf\n", error(Up, Down, Num, dx));
}