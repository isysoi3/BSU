import numpy as np
import random
import time
import math
import matplotlib.pyplot as plt


def func(x):
    return ((x ** 9 + math.pi) * math.cos(math.log(x ** 2 + 1))) / (math.e ** (x ** 2)) - (x / 2018)


def derivative_func(f, x):
    h = 0.000001
    return (f(x+h) - f(x)) / h


def bisection(f, a, b, eps):
    while abs(b - a) > 2 * eps:
        c = (a + b) / 2
        if f(c) * f(a) < 0:
            b = c
        else:
            a = c
    return a, b


def discrete_newtons_method(f, x0, eps):
    x = x0
    h = 0.000001
    while abs(f(x)) > eps:
        x = x - ((f(x) * h) / (f(x + h) - f(x)))
    return x


def newton_method(f, derivative_f, x0, eps):
    x = x0
    while abs(f(x)) > eps:
        next_x = x - f(x) / derivative_f(f, x)
        x = next_x
    return x


def equidistant_nodes(a, b, n):
    return [a + (b-a)/(n-1) * i for i in range(n)]


def chebyshev_nodes(a, b, n):
    center = (a+b)/2
    half_len = (b-a)/2
    return [center + half_len * math.cos(math.pi * (2*i+1)/(2*n+2)) for i in range(n)]


def main(showPlots=True):
    print(bisection(func, -2.40, -1.75, 10e-5))
    print(bisection(func, -1.45, -0.75, 10e-5))
    print(bisection(func, 1.75, 2.45, 10e-5))

    print(discrete_newtons_method(func, -2.45, 10e-6)) #TODO: see this
    print(newton_method(func, derivative_func, -2.45, 10e-6)) #TODO: see this
    print(chebyshev_nodes(-4, 4, 6))
    print(equidistant_nodes(-4, 4, 6))


if __name__ == '__main__':
    main()
