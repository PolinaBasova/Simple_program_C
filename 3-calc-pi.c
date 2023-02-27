#include <stdio.h>
#include <math.h>

void print_pi(int N);
double expotentiation(int degree, double basis);


int main() {
    int N;
    printf("Input a precision: N = ");
    scanf("%d", &N);
    print_pi(N);
}

double expotentiation(int degree, double basis) {
    double result = 1;
    for (int i=1; i <= degree; i++) {
        result *= basis;
    }
    return result;
}

void print_pi(int N) {
    double SumUp = 0, SumDown=0;
    int n=0;
    do {
        n++;
        SumUp = SumDown + (4/double(2*n-1)) ;
        n++;
        SumDown = SumUp - (4/double(2*n-1));
    } while (  fabs(SumUp - SumDown) >= expotentiation(N, 0.1) );
    printf("%.*f\n", N, fabs(SumUp - SumDown));
    printf("%.*f\n", N, ((SumUp+SumDown)/2));
}