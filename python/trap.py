import asyncio

from sys import argv
from math import e, sin

def integral(f, r: tuple, n: int) -> float:
    """Calculates the integral of f over range"""
    a, b = r
    dx = (b - a) / n
    int_sum = 0

    async def compute(i):
        x = a + i*dx
        return f(x)

    # compute the endpoints
    int_sum += (f(a) + f(b)) / 2

    # create jobs
    jobs = map(compute, range(0, n))

    loop = asyncio.get_event_loop()
    # compute the integral
    g = asyncio.gather(*jobs)
    res = loop.run_until_complete(g)
    loop.close()

    int_sum += sum(res)

    int_sum = int_sum * dx

    return int_sum

def main(args: list):
    a = float(args[1])
    b = float(args[2])

    f = lambda x: (e**(3 * x)) * sin(2 * x)

    val = integral(f, (a, b), 1000)

    print(val)

if __name__ == "__main__":
    main(argv)