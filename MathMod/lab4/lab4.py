"""

Вычислить значение интеграла, используя метод Монте-Карло. Оценить точность.

По методу Монте-Карло вычислить приближенное значения интегралов.
Сравнить полученное значение либо с точным значением (если его получится вычислить), либо с приближенным, полученным в каком-либо математическом пакете (например, в mathematica). Для этого построить график зависимости точности вычисленного методом Монте-Карло интеграла от числа итераций n.

"""

import numpy as np
import scipy.integrate as integrate
import matplotlib.pyplot as plt
from math import exp, log
from scipy.stats import cauchy
from random import uniform, random


def integral_1(x):
    return exp(x) * log(x)


def integral_2(x,y):
    return exp(- (x**2 + y**2)/2) * log(1 + (2*x - 3*y)**2)


def bounds():
    return [-np.inf, np.inf]


def calculate_integral(integrand, a, b, n=100):
    return sum([integrand(a + (b - a) * random()) for _ in range(n)]) * (b - a) / n


def print_info(mk, math):
    print("Значение по Монте-Карло", mk,
          "\nПриближенное, полученное в математическом пакете", math)

def main():
    i1 = integrate.quad(integral_1, 1, 3)[0]
    i1_test = calculate_integral(integral_1, 1, 3)
    print_info(i1_test, i1)
    i2 = integrate.nquad(integral_2, [bounds(), bounds()])[0]
    print(i2)




if __name__ == '__main__':
    main()
