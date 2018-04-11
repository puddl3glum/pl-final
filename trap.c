
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
double integral(double (*f)(double), Pair range, double tolerance) {
    // return (*f)(range.a);
    List stack = new_list();
    //printf("%d\n", empty(&stack));
    //printf("%x\n", &stack);
    //printf("%f %f\n", range.a, range.b);
    push(&stack, range);
    //printf("%d\n", empty(&stack));

    //Pair popped = pop(&stack);
    //printf("%f %f\n", popped.a, popped.b);

    //printf("%d\n", empty(&stack));
    //Pair top = stack.top->range;
    //printf("%f %f\n", top.a, top.b);
    //return;

    // integral value
    double I = 0;

    #pragma omp parallel for shared(I, stack)
    //for (;!empty(&stack);) {
    for (int i = 0; i < 100; i++) {
        //puts("loop");
        // if () {
        //     break;
        // }
        
        if (empty(&stack)) {
            continue;
        }
        // interval [a,b] on top of stack removed from stack
        Pair local_range = pop(&stack);
        double a = local_range.a;
        double b = local_range.b;
        double I_1 = ((b - a) / 2) * ((*f)(a) + (*f)(b));
        //printf("%f\n", I_1);

        //printf("%f %f\n", a, b);
        // return;
        double m = (a + b) / 2;

        double I_2 = ((b - a) / 4) * ((*f)(a) + 2 * (*f)(m) + (*f)(b));

        if (fabs(I_1 - I_2) < 3 * (b - a) * tolerance) {
            //puts("hi");
            I = I + I_2;
        } else {
            //puts("hey");
            push(&stack, (Pair){a, m});
            push(&stack, (Pair){m, b});
        }

    }

    return I;

}

int main() {

    // declare function pointer
    double (*fPtr)(double);

    fPtr = &f;

    //Pair range = (Pair){0, PI/4};
    Pair range = (Pair){0, 10};
    
    printf("%.16f\n", integral(f, range, 0.000000001));
}