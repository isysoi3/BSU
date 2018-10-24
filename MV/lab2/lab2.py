import math
import random

import matplotlib.pyplot as plt
import numpy as np


def func(x):
    return ((x ** 9 + math.pi) * math.cos(math.log(x ** 2 + 1))) / (math.e ** (x ** 2)) - (x / 2018)


def derivative_func(f, x):
    h = 0.000001
    return (f(x + h) - f(x)) / h


def show_plot(f):
    def wrapper(*args, **kwargs):
        res = f(*args, **kwargs)
        x = random_points_X(-5, 5, 10000)
        y = [func(pointX) for pointX in x]

        plt.title(args[-1])
        plt.plot(x, y, label='original')
        plt.plot(res[0], res[1], label='new')

        plt.legend(loc='upper left')
        plt.ylim(-5, 5)
        plt.grid(True)
        plt.show()

    return wrapper


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
    return [a + (b - a) / (n - 1) * i for i in range(n)]


def chebyshev_nodes(a, b, n):
    center = (a + b) / 2
    half_len = (b - a) / 2
    return [center + half_len * math.cos(math.pi * (2 * i + 1) / (2 * n + 2)) for i in range(n)]


def newton_interpolation_coefficients(f, x_array):
    n = len(x_array)
    coef = np.zeros((n, n))
    for i in range(n):
        if i == 0:
            coef[:, i] = [f(x) for x in x_array]
        else:
            coef[i:n, i] = [(coef[j, i - 1] - coef[j - 1, i - 1]) / (x_array[j] - x_array[j - i]) for j in range(i, n)]
    return coef.diagonal()


@show_plot
def newton_interpolation(f, x_array, name):
    coefficients = newton_interpolation_coefficients(f, x_array)
    rez_string = ""
    for i, coefficient in enumerate(coefficients):
        if i != 0:
            rez_string += "+" if coefficient > 0 else ""
        rez_string += ("*".join([str(coefficient)]
                                + [("(x" + (
            (("+" if x_array[j] < 0 else "-") + str(abs(x_array[j]))) if x_array[j] != 0 else "") + ")") for j in
                                   range(i)]))

    x = random_points_X(-5, 5, 10000)
    y = [sum([coefficient * np.prod([(pointX - x_array[j]) for j in range(i)]) for i, coefficient in
              enumerate(coefficients)]) for pointX in x]
    return x, y


def binomial_coefficient(n, i):
    return math.factorial(n) / (math.factorial(i) * math.factorial(n - i))


@show_plot
def bezier(n, name):
    points_x = random_points_X(-4, 4, n)
    points_y = [func(x) for x in points_x]
    tmp = [sum(
        [binomial_coefficient(n, i) * (t ** i) * ((1 - t) ** (n - 1 - i)) * point for i, point in enumerate(points_y)])
        for t in [re / n for re in range(n)]]
    return points_x, tmp


def random_points_X(a, b, n):
    return sorted([random.uniform(a, b) for _ in range(n)])


@show_plot
def rms_approximation(f, points, n, name):
    n += 1
    beta = np.zeros(n)
    gamma = np.zeros((n, n))
    for i in range(n):
        beta[i] = sum([f(point) * (point ** i) for point in points])
        gamma[i, :] = [sum([(point ** j) * (point ** i) for point in points]) for j in range(n)]

    coef = np.linalg.solve(gamma, beta)
    x = random_points_X(-5, 5, 1000)
    y = [sum([coef[i] * pointX ** i for i in range(n)]) for pointX in x]
    return x, y


@show_plot
def spline(f, x_points, name):
    n = len(x_points)
    splines_count = n - 1
    matrix = np.zeros((4 * splines_count, 4 * splines_count))
    b = np.zeros(4 * splines_count)
    y_points = [f(x) for x in x_points]

    for i in range(splines_count):
        b[i * 2] = y_points[i]
        b[i * 2 + 1] = y_points[i + 1]
        for j in range(4):
            matrix[i * 2, i * 4 + j] = x_points[i] ** (3 - j)
            matrix[i * 2 + 1, i * 4 + j] = x_points[i + 1] ** (3 - j)

    for i in range(1, splines_count):
        for j in range(3):
            matrix[2 * splines_count + i - 1,
                   (i - 1) * 4 + j] = (3 - j) * x_points[i] ** (2 - j)
            matrix[2 * splines_count + i - 1,
                   i * 4 + j] = -(3 - j) * x_points[i] ** (2 - j)

    for i in range(1, splines_count):
        for j in range(2):
            matrix[3 * splines_count + i - 2,
                   (i - 1) * 4 + j] = 2 * (2 - j) * x_points[i] ** (1 - j)
            matrix[3 * splines_count + i - 2,
                   i * 4 + j] = -2 * (2 - j) * x_points[i] ** (1 - j)

    for j in range(3):
        matrix[-2, j] = (3 - j) * x_points[0] ** (2 - j)
        matrix[-1, -3 + j] = (3 - j) * x_points[-1] ** (2 - j)

    np.set_printoptions(threshold=np.nan)
    coef = np.linalg.solve(matrix, b)

    rez_x = []
    rez_y = []
    for i in range(1, len(x_points)):
        random_x_points = equidistant_nodes(x_points[i - 1], x_points[i], 100)
        rez_x += random_x_points
        for point in random_x_points:
            new_y_point = sum([coef[(i - 1) * 4 + j] * point ** (3 - j) for j in range(4)])
            rez_y.append(new_y_point)

    return rez_x, rez_y


def main(showPlots=True):
    # print(bisection(func, -2.40, -1.75, 10e-5))
    # print(bisection(func, -1.45, -0.75, 10e-5))
    # print(bisection(func, 1.75, 2.45, 10e-5))
    #
    # print(discrete_newtons_method(func, -2.45, 10e-6)) #TODO: see this
    # print(newton_method(func, derivative_func, -2.45, 10e-6)) #TODO: see this
    #
    # newton_interpolation(func, equidistant_nodes(-4, 4, 6), "6 равноотстоящих узлаов")
    # newton_interpolation(func, equidistant_nodes(-4, 4, 12), "12 равноотстоящих узлаов")
    # newton_interpolation(func, equidistant_nodes(-4, 4, 18), "18 равноотстоящих узлаов")
    #
    # newton_interpolation(func, chebyshev_nodes(-4, 4, 6), "6 узлов Чебышева")
    # newton_interpolation(func, chebyshev_nodes(-4, 4, 12), "12 узлов Чебышева")
    # newton_interpolation(func, chebyshev_nodes(-4, 4, 18), "18 узлов Чебышева")
    #
    # bezier(40, "Кривая Безье")
    #
    # rms_approximation(func, random_points_X(-4, 4, 100), 1, "Cреднеквадратичные приближения, n = 1")
    # rms_approximation(func, random_points_X(-4, 4, 100), 2, "Cреднеквадратичные приближения, n = 2")
    # rms_approximation(func, random_points_X(-4, 4, 100), 3, "Cреднеквадратичные приближения, n = 3")
    # rms_approximation(func, random_points_X(-4, 4, 100), 4, "Cреднеквадратичные приближения, n = 4")
    # rms_approximation(func, random_points_X(-4, 4, 100), 5, "Cреднеквадратичные приближения, n = 5")
    # rms_approximation(func, random_points_X(-4, 4, 100), 6, "Cреднеквадратичные приближения, n = 6")

    spline(func, equidistant_nodes(-4, 4, 6), "Cплайн третьего порядка на 6 узлах")
    spline(func, equidistant_nodes(-4, 4, 12), "Cплайн третьего порядка на 12 узлах")
    spline(func, equidistant_nodes(-4, 4, 18), "Cплайн третьего порядка на 18 узлах")


if __name__ == '__main__':
    main()
