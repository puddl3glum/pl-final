
import asyncio
import time

from collections import deque
from math import e, sin
from multiprocessing import cpu_count
from sys import argv
from typing import Deque

def integral(f, r: tuple, tol: float) -> float:
    """Calculates the integral of f over range"""

    # set up a "stack"
    stack: Deque = deque()

    async def compute(idx: int):
        # compute integral for range
        a, b = stack.pop()

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
            stack.append((a, m))
            stack.append((m, b))
            # return 0 b/c no
            return 0

    # put first range on stack
    stack.append(r)

    loop = asyncio.get_event_loop()

    int_sum = 0

    while stack:
        # while the stack is not empty, compute the integral
        # map over every element of the stack
        jobs = map(compute, range(0, len(stack)))
        # compute the integral
        g = asyncio.gather(*jobs)
        res = loop.run_until_complete(g)
        int_sum += sum(res)
    
    loop.close()

    return int_sum

def main(args: list):
    a = float(args[1])
    b = float(args[2])

    tol = float(args[3])

    # print(cpu_count())

    f = lambda x: (e**(3 * x)) * sin(2 * x)
    # f = lambda x: x**2

    val = integral(f, (a, b), tol)

    print(val)

if __name__ == "__main__":
    main(argv)