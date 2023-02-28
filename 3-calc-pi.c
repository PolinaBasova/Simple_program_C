#include <stdio.h>
#include <math.h>

double calc_pi(int N);

int main() {
    int N;
    printf("Input a precision: N = ");
    scanf("%d", &N);
    printf("%.*f\n", N, calc_pi(N));
}

double calc_pi(int N) {
    double SumUp = 0, SumDown=0;
    int n=0;
    do {
        n++;
        SumUp = SumDown + (4/double(2*n-1)) ;
        n++;
        SumDown = SumUp - (4/double(2*n-1));
    } while (  fabs(SumUp - SumDown) >= pow(0.1, N) );
    return ((SumUp+SumDown)/2);
}