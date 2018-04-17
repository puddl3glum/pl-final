
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "pair.h"
#include "stack.h"

const double PI = 4 * atan(1);

// function: f(x) = x^2
double f (double x) {
    return exp(3 * x) * sin(2 * x);
}

// integral function
double integral(double (*f)(double), Pair range, int n) {

    double  h, x, integral = 0.0;

    int i;

    double a = range.a;
    double b = range.b;
    
    h = (b-a)/n;
    integral += ((*f)(a) + (*f)(b))/2.0;
    
    #pragma omp parallel for schedule(static) default(none) \
    shared(a, h, n, f) private(i, x) \
    reduction(+: integral) //num_threads(thread_count)

    for (i = 1; i <= n - 1; i++) {
        x = a + i*h;
        integral += (*f)(x);
        
    }
    
    integral = integral*h;
    
    return integral;

}

int main(int argc, char * argv[]) {

    double a, b;

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    // declare function pointer
    double (*fPtr)(double);

    fPtr = &f;

    //Pair range = (Pair){0, PI/4};
    Pair range = (Pair){a, b};
    
    printf("%.16f\n", integral(f, range, 10000));
}
