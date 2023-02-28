#include <stdio.h>
#include <math.h>

double calc_pi(int Prec);

int main() {
    int Prec;
    printf("Input a precision: Prec = ");
    scanf("%d", &Prec);
    printf("%.*f\n", Prec, calc_pi(Prec));
}

double calc_pi(int Prec) {
    double SumUp = 0, SumDown=0;
    int n=0;
    do {
        n++;
        SumUp = SumDown + (4/double(2*n-1)) ;
        n++;
        SumDown = SumUp - (4/double(2*n-1));
    } while (  fabs(SumUp - SumDown) >= pow(0.1, Prec) );
    return ((SumUp+SumDown)/2);
}