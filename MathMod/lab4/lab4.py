"""

Вычислить значение интеграла, используя метод Монте-Карло. Оценить точность.

По методу Монте-Карло вычислить приближенное значения интегралов.
Сравнить полученное значение либо с точным значением (если его получится вычислить), либо с приближенным,
полученным в каком-либо математическом пакете (например, в mathematica).
Для этого построить график зависимости точности вычисленного методом Монте-Карло интеграла от числа итераций n.

"""

import numpy as np
import scipy.integrate as integrate
import matplotlib.pyplot as plt
from matplotlib import rc
from math import exp, log
from scipy.stats import cauchy
from random import uniform, random


def integral_1(x):
    return exp(x) * log(x)


def integral_2(x, y):
    return exp(- (x**2 + y**2)/2) * log(1 + (2*x - 3*y)**2)


def bounds():
    return [-np.inf, np.inf]


def calculate_integral(integrand, a, b, n=1000):
    return sum([integrand(a + (b - a) * random()) for _ in range(n)]) * (b - a) / n

def calc_first(n=1000):
    return calculate_integral(integral_1, 1, 3, n)


def print_info(mk, math):
    print("Значение по Монте-Карло", mk,
          "\nПриближенное, полученное в математическом пакете", math)


def get_numbers():
    return (2**x for x in range(18))


def test(func):
    m = 10
    return [sum([func(n) for _ in range(m)]) / m for n in get_numbers()]


def draw(real, theory):
    rc('ytick', labelsize=15)
    rc('xtick', labelsize=15)
    plt.figure(figsize=(20, 8))
    x = list(get_numbers())
    plt.plot(x, [theory]*len(x), label='theory')
    plt.plot(x, real, label='real')
    plt.xscale('log')
    plt.xticks(x, x)
    plt.xlabel('n - number of iterations', fontsize=20)
    plt.ylabel('integral value', fontsize=20)
    plt.legend()
    plt.show()


def main():
    i1 = integrate.quad(integral_1, 1, 3)[0]
    i1_test = calculate_integral(integral_1, 1, 3)
    print_info(i1_test, i1)

    i2_test = 0
    i2 = integrate.nquad(integral_2, [bounds(), bounds()])[0]
    print_info(i2_test, i2)

    i1_real = test(calc_first)
    draw(i1_real, i1)
    #draw(i2_real, i2)


if __name__ == '__main__':
    main()
