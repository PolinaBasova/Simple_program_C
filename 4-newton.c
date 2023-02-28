#include <stdio.h>
#include <math.h>

double Func(double x){
    return x*x;
}

double dFunc(double x){
    double dx = pow(0.1, -100);
    return ((Func(x+dx)-Func(x))/dx);
}


int main() {
    double Max, Min;
    printf("Input approximation Max = ");
    
    printf("Max = ");
    
    
}
