import itertools
import math

import operator
from functools import reduce

import random
import time
import matplotlib.pyplot as plt
import numpy as np
import pylab
from mpl_toolkits.mplot3d import Axes3D

file = open("out.txt", mode="w")
is_show_plot = False


def func_f(x):
    return ((x ** 9 + math.pi) * math.cos(math.log(x ** 2 + 1))) / (math.e ** (x ** 2)) - (x / 2018)


def func_g(x, y):
    return (x ** 9 + math.pi) * math.cos(math.log(y ** 4 + 1)) / ((math.e ** (x ** 2)) * (y ** 2 + math.e))


def derivative_func(f, x):
    h = 0.000001
    return (f(x + h) - f(x)) / h


def show_plot(f):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        res = f(*args, **kwargs)
        print("Время на", args[-1].lower(), time.time() - start_time, file=file)

        x = random_points_X(-5, 5, 10000)
        y = [func_f(pointX) for pointX in x]

        plt.title(args[-1])
        plt.plot(x, y, label='original')
        plt.plot(res[0], res[1], label='new')
        plt.plot(y=0, color='red')

        plt.legend(loc='upper left')
        plt.ylim(-5, 5)
        plt.grid(True)

        fig1 = plt.gcf()
        if is_show_plot:
            plt.show()
        plt.draw()
        fig1.savefig("plots/" + args[-1].lower() + ".png", dpi=100)
        plt.close()

    return wrapper


def show_plot3D(f):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        X, Y, Z = f(*args, **kwargs)
        print("Время на", args[-1].lower(), time.time() - start_time, file=file)

        plt.title(args[-1])
        plt.style.use("ggplot")
        plt.rcParams['figure.figsize'] = (15, 5)
        fig = plt.figure()
        ax = fig.gca(projection='3d')
        ax.set_zlim(-3, 3)

        ax.plot_surface(X, Y, Z)
        if is_show_plot:
            plt.show()
        plt.draw()
        fig.savefig("plots/" + args[-1].lower() + ".png", dpi=100)
        plt.close()

    return wrapper


def bisection(f, a, b, eps):
    steps = 0
    while abs(b - a) > 2 * eps:
        c = (a + b) / 2
        if f(c) * f(a) < 0:
            b = c
        else:
            a = c
        steps += 1
    return a, b, steps


def discrete_newtons_method(f, x0, eps):
    x = x0
    h = 0.000001
    steps = 0
    while abs(f(x)) > eps:
        x = x - ((f(x) * h) / (f(x + h) - f(x)))
        steps += 1
    return x, steps


def newton_method(f, derivative_f, x0, eps):
    x = x0
    steps = 0
    while abs(f(x)) > eps:
        x = x - f(x) / derivative_f(f, x)
        steps += 1
    return x, steps


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

    x = equidistant_nodes(-5, 5, 1000)
    y = [sum([coefficient * np.prod([(pointX - x_array[j]) for j in range(i)]) for i, coefficient in
              enumerate(coefficients)]) for pointX in x]

    return x, y


def binomial_coefficient(n, i):
    return math.factorial(n) / (math.factorial(i) * math.factorial(n - i))


@show_plot
def bezier(n, name):
    points_x = random_points_X(-4, 4, n)
    points_y = [func_f(x) for x in points_x]
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
            if j > 3:
                continue
            matrix[2 * splines_count + i - 1,
                   (i - 1) * 4 + j] = (3 - j) * x_points[i] ** (2 - j)
            matrix[2 * splines_count + i - 1,
                   i * 4 + j] = -(3 - j) * x_points[i] ** (2 - j)
            if j > 2:
                continue
            matrix[3 * splines_count + i - 2,
                   (i - 1) * 4 + j] = 2 * (2 - j) * x_points[i] ** (1 - j)
            matrix[3 * splines_count + i - 2,
                   i * 4 + j] = -2 * (2 - j) * x_points[i] ** (1 - j)

    for j in range(3):
        matrix[-2, j] = (3 - j) * x_points[0] ** (2 - j)
        matrix[-1, -3 + j] = (3 - j) * x_points[-1] ** (2 - j)

    coefficients = np.linalg.solve(matrix, b)

    rez_x = []
    rez_y = []
    for i in range(1, len(x_points)):
        random_x_points = equidistant_nodes(x_points[i - 1], x_points[i], 100)
        rez_x += random_x_points
        for point in random_x_points:
            new_y_point = sum([coefficients[(i - 1) * 4 + j] * point ** (3 - j) for j in range(4)])
            rez_y.append(new_y_point)

    return rez_x, rez_y


@show_plot3D
def interpolation_x_y(f, x_points, y_points, name):
    z_points = np.array([[func_g(x_tmp, y_tmp) for y_tmp in y_points] for x_tmp in x_points])
    n = len(z_points)
    x = random_points_X(-4, 4, 100)
    y = random_points_X(-4, 4, 100)

    Z = np.array(
        [[sum([sum([z_points[i, j]
                    * reduce(operator.mul, [(x_tmp - x[p]) / (x[i] - x[p]) for p in range(n) if i != p])
                    * reduce(operator.mul, [(y_tmp - y[p]) / (y[j] - y[p]) for p in range(n) if j != p]) for j in
                    range(n)]) for i in range(n)]) for y_tmp in y] for x_tmp in x]
    )

    X, Y = np.meshgrid(x, y)
    return X, Y, Z


def center_rectangle(a, b, h, f):
    n = (b - a) / h
    n = int(n)

    return h * sum([f(a + (k - 1 / 2) * h) for k in range(1, n + 1)])


def left_rectangle(a, b, h, f):
    n = (b - a) / h
    n = int(n)

    return h * sum([f(a + k * h) for k in range(0, n)])


def right_rectangle(a, b, h, f):
    n = (b - a) / h
    n = int(n)

    return h * sum([f(a + k * h) for k in range(1, n + 1)])


def trapezoid(a, b, h, f):
    n = (b - a) / h
    n = int(n)

    return h / 2 * (f(a) + 2 * sum([f(a + k * h) for k in range(1, n)]) + f(b))


def simpson(a, b, h, f):
    n = (b - a) / h
    n = int(n)

    return h / 3 * sum([f(a + (k - 1) * h) + 4 * f(a + (k - 1) * h) + f(a + (k + 1) * h) for k in range(1, n, 2)])


def gauus_2_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [1, 1]

    return h / 2 * sum(
        [sum([f(((a + k * h) + (a + (k + 1) * h)) / 2 + ((a + (k + 1) * h) - (a + k * h)) / coef) for coef in coefs])
         for k in range(n)])


def gauus_3_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [0.5555556, 0.8888889, 0.5555556]
    nodes = [0.77459666924148337703, 0, 0.7745966692414833770]

    return h / 2 * sum(
        [sum([coef * f(h / 2 * node + ((a + (k + 1) * h) + (a + k * h)) / 2) for coef, node in zip(coefs, nodes)]) for k
         in range(n)])


def gauus_4_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [0.3478548, 0.6521451, 0.6521451, 0.3478548]
    nodes = [-0.86113631159405257522, -0.33998104358485626480, 0.86113631159405257522, 0.33998104358485626480]

    return h / 2 * sum(
        [sum([coef * f(h / 2 * node + ((a + (k + 1) * h) + (a + k * h)) / 2) for coef, node in zip(coefs, nodes)]) for k
         in range(n)])


def gauus_5_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [0.568888888888888888889, 0.23692688505618908751, 0.47862867049936646804, 0.23692688505618908751,
             0.47862867049936646804]
    nodes = [0, -0.90617984593866399279, -0.53846931010568309103, 0.90617984593866399279, 0.53846931010568309103]

    return h / 2 * sum(
        [sum([coef * f(h / 2 * node + ((a + (k + 1) * h) + (a + k * h)) / 2) for coef, node in zip(coefs, nodes)]) for k
         in range(n)])


def gauus_6_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [0.46791393457269104738, 0.36076157304813860756, 0.17132449237917034504, 0.46791393457269104738,
             0.36076157304813860756, 0.17132449237917034504]
    nodes = [-0.23861918608319690863, -0.66120938646626451366, -0.93246951420315202781, 0.23861918608319690863,
             0.66120938646626451366, 0.93246951420315202781]

    return h / 2 * sum(
        [sum([coef * f(h / 2 * node + ((a + (k + 1) * h) + (a + k * h)) / 2) for coef, node in zip(coefs, nodes)]) for k
         in range(n)])


def gauus_7_nodes(a, b, h, f):
    n = (b - a) / h
    n = int(n)
    coefs = [0.41795918367346938775, 0.38183005050511894495, 0.27970539148927666790, 0.12948496616886969327,
             0.38183005050511894495, 0.27970539148927666790, 0.12948496616886969327]
    nodes = [0, -0.40584515137739716690, -0.74153118559939443986, -0.94910791234275852452, 0.40584515137739716690,
             0.74153118559939443986, 0.94910791234275852452]

    return h / 2 * sum(
        [sum([coef * f(h / 2 * node + ((a + (k + 1) * h) + (a + k * h)) / 2) for coef, node in zip(coefs, nodes)]) for k
         in range(n)])


def main():
    root_segments = [(-2.40, -1.75), (-1.45, -0.75), (1.75, 2.45)]
    for left, right in root_segments:
        a, b, steps = bisection(func_f, left, right, 10e-5)
        print("Отрезок (" + str(a) + ", " + str(b) + ").", "Шагов", steps, file=file)
        rez, steps = discrete_newtons_method(func_f, a, 10e-9)
        print("Дискретный вариант метода Ньютона =", rez, "Шагов", steps, file=file)
        rez, steps = newton_method(func_f, derivative_func, rez, 10e-15)
        print("Метод Ньютона =", rez, "Шагов", steps, file=file)
        print(file=file)

    print(file=file)
    newton_interpolation(func_f, equidistant_nodes(-4, 4, 6), "6 равноотстоящих узлаов")
    newton_interpolation(func_f, equidistant_nodes(-4, 4, 12), "12 равноотстоящих узлаов")
    newton_interpolation(func_f, equidistant_nodes(-4, 4, 18), "18 равноотстоящих узлаов")

    print(file=file)
    newton_interpolation(func_f, chebyshev_nodes(-4, 4, 6), "6 узлов Чебышева")
    newton_interpolation(func_f, chebyshev_nodes(-4, 4, 12), "12 узлов Чебышева")
    newton_interpolation(func_f, chebyshev_nodes(-4, 4, 18), "18 узлов Чебышева")

    print(file=file)
    spline(func_f, equidistant_nodes(-4, 4, 6), "Cплайн третьего порядка на 6 узлах")
    spline(func_f, equidistant_nodes(-4, 4, 12), "Cплайн третьего порядка на 12 узлах")
    spline(func_f, equidistant_nodes(-4, 4, 18), "Cплайн третьего порядка на 18 узлах")

    print(file=file)
    bezier(40, "Кривая Безье")

    print(file=file)
    rms_approximation(func_f, random_points_X(-4, 4, 100), 1, "Cреднеквадратичные приближения, n = 1")
    rms_approximation(func_f, random_points_X(-4, 4, 100), 2, "Cреднеквадратичные приближения, n = 2")
    rms_approximation(func_f, random_points_X(-4, 4, 100), 3, "Cреднеквадратичные приближения, n = 3")
    rms_approximation(func_f, random_points_X(-4, 4, 100), 4, "Cреднеквадратичные приближения, n = 4")
    rms_approximation(func_f, random_points_X(-4, 4, 100), 5, "Cреднеквадратичные приближения, n = 5")
    rms_approximation(func_f, random_points_X(-4, 4, 100), 6, "Cреднеквадратичные приближения, n = 6")

    print(file=file)
    interpolation_x_y(func_g,
                      equidistant_nodes(-4, 4, 6),
                      equidistant_nodes(-6, 6, 6),
                      "интерполяционные многочлены двух переменны 6x6")
    interpolation_x_y(func_g,
                      equidistant_nodes(-4, 4, 12),
                      equidistant_nodes(-6, 6, 12),
                      "интерполяционные многочлены двух переменны 12x12")
    interpolation_x_y(func_g,
                      equidistant_nodes(-4, 4, 18),
                      equidistant_nodes(-6, 6, 18),
                      "интерполяционные многочлены двух переменны 18x18")

    result = 4.967532679086564
    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("средних прямоугольников i =", i,
              ", разность =", center_rectangle(-4, 4, 8 / (4 ** i), func_f) - result,
              ",время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Левых прямоугольников i =", i,
              ", разность =", left_rectangle(-4, 4, 8 / (4 ** i), func_f) - result,
              ",время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Правых прямоугольников i =", i,
              ", разность =", right_rectangle(-4, 4, 8 / (4 ** i) - result, func_f),
              ",время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Tрапеций i =", i,
              ", разность =", trapezoid(-4, 4, 8 / (4 ** i), func_f) - result,
              ", время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Симпсон i =", i,
              ", разность =", simpson(-4, 4, 8 / (4 ** i), func_f) - result,
              ", время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 2 узлам i =", i,
              ", разность =", gauus_2_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 3 узлам i =", i,
              ", разность =", gauus_3_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время =", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 4 узлам i =", i,
              "разность =", gauus_4_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время ", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 5 узлам i =", i,
              ", разность =", gauus_5_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время ", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 6 узлам i =", i,
              ", разность =", gauus_6_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время ", time.time() - start_time, file=file)

    print(file=file)
    for i in range(0, 11):
        start_time = time.time()
        print("Гаусс по 7 узлам i =", i,
              ", разность =", gauus_7_nodes(-4, 4, 8 / (4 ** i) - result, func_f),
              ", время ", time.time() - start_time, file=file)


if __name__ == '__main__':
    main()
