#!/usr/bin/env python3

import time

from collections import deque
from math import e, sin
from multiprocessing import Pool, cpu_count
from sys import argv
from typing import Deque, Callable

def compute(env: tuple):
    # compute integral for range
    f, subrange, tol = env
    a, b = subrange

    # trapezoidal rule
    I_1 = ((b - a) / 2)*(f(a) + f(b))
    # get midpoint
    m = (a + b) / 2
    # composite trapezoidal rule w/ 2 subintervals
    I_2 = ((b - a) / 4)*(f(a) + 2*f(m) + f(b))

    if abs(I_1 - I_2) < 3 * (b - a) * tol:
        # if less than the tolerance, return calculated val
        return I_2
    else:
        return (f, (a, m), tol), (f, (m, b), tol)

def integral(f, r: tuple, tol: float) -> float:
    """Calculates the integral of f over range"""

    # set up a "stack"
    # put first range on stack
    stack = [(f, r, tol)]

    int_sum = 0

    while stack:
        # while the stack is not empty, compute the integral
        # map over every element of the stack

        with Pool(cpu_count()) as p:
            ret_list = p.map(compute, stack)
            int_sum += sum(filter(lambda x: type(x) == float, ret_list))

            tuples = filter(lambda x: type(x) == tuple, ret_list)
            
            stack = []
            for t in tuples:
                t0, t1 = t
                stack += [t0, t1]

    return int_sum

def f(x):
    return (e**(3 * x)) * sin(2 * x)

def main(args: list):
    a = float(args[1])
    b = float(args[2])

    tol = float(args[3])

    val = integral(f, (a, b), tol)

    print(val)

if __name__ == "__main__":
    main(argv)