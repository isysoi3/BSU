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


def newton_interpolation_coefficients(f, x_array):
    n = len(x_array)
    coef = np.zeros((n, n))
    for i in range(n):
        if i == 0:
            coef[:, i] = [f(x) for x in x_array]
        else:
            coef[i:n, i] = [(coef[j, i - 1] - coef[j - 1, i - 1]) / (x_array[j] - x_array[j - i]) for j in range(i, n)]
    return coef.diagonal()


def newton_interpolation(f, x_array):
    coefficients = newton_interpolation_coefficients(f, x_array)
    rez_string = ""
    for i, coefficient in enumerate(coefficients):
        if i != 0:
            rez_string += "+" if coefficient > 0 else ""
        rez_string += ("*".join([str(coefficient)]
                       + [("(x" + ((("+" if x_array[j] < 0 else "-") + str(abs(x_array[j]))) if x_array[j] != 0 else "") + ")") for j in range(i)]))

    return rez_string


def binomial_coefficient(n, i):
    return math.factorial(n) / (math.factorial(i) * math.factorial(n-i))


def bezier(t, points):
    n = len(points)
    return sum([ binomial_coefficient(n, i) * (t**i) * ((1-t)**(n-1-i)) * point for i, point in enumerate(points)])


def random_points(a, b, n):
    return sorted([random.uniform(a, b) for _ in range(n)])


def rms_approximation(f, points, n):
    n += 1
    beta = np.zeros(n)
    gamma = np.zeros((n,n))
    for i in range(n):
        beta[i] = sum([f(point) * (point ** i) for point in points])
        gamma[i, :] = [sum([(point**j)*(point**i) for point in points]) for j in range(n)]

    print(np.linalg.solve(gamma, beta))
    return "+".join(["*".join(pair) for pair in zip(["x**" + str(i) for i in range(n)], list(map(str, np.linalg.solve(gamma, beta))))])

def main(showPlots=True):
    print(bisection(func, -2.40, -1.75, 10e-5))
    print(bisection(func, -1.45, -0.75, 10e-5))
    print(bisection(func, 1.75, 2.45, 10e-5))

    print(discrete_newtons_method(func, -2.45, 10e-6)) #TODO: see this
    print(newton_method(func, derivative_func, -2.45, 10e-6)) #TODO: see this
    print(chebyshev_nodes(-4, 4, 6))
    print(equidistant_nodes(-4, 4, 6))
    print(equidistant_nodes(-2, 2, 5))
    print(newton_interpolation(func, equidistant_nodes(-2, 2, 5)))

    print(rms_approximation(tmp, [1, 2, 3], 2))

def tmp(x):
    return x


if __name__ == '__main__':
    main()


# генерация случайных точек на отрезке [a,b]
# def generateXY(a, b, count):
#     xlist = [random.uniform(a, b) for _ in range(count)]
#     xlist = sorted(xlist)
#     ylist = [func(x) for x in xlist]
#
#     return np.array(xlist), np.array(ylist)
#
#
# # точки для графика исходной функции
# def basicPlot(a, b, pointsCount):
#     x, y = generateXY(a, b, pointsCount)
#     return x, y
#
#
# ## график заданной функции и исходной функции
# def funcPlot(func):
#     import matplotlib.pyplot as plt
#
#     def wrapper(*args, **kwargs):
#         fig = plt.figure()
#         res = func(*args, **kwargs)
#         x, y = basicPlot(-4, 4, 1000)
#
#         plt.plot(x, y)
#         plt.plot(res[0], res[1], marker='o')
#         plt.grid(True)
#         plt.show()c
#
#     return wrapper
#
#
# @funcPlot
# def RMSApproximation(x, y, N, basis):
#     # код функции
#     return 0