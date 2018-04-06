"""

Вычислить значение интеграла, используя метод Монте-Карло. Оценить точность.

По методу Монте-Карло вычислить приближенное значения интегралов.
Сравнить полученное значение либо с точным значением (если его получится вычислить), либо с приближенным, полученным в каком-либо математическом пакете (например, в mathematica). Для этого построить график зависимости точности вычисленного методом Монте-Карло интеграла от числа итераций n.


	￼
"""

import numpy as np
import scipy.integrate as integrate
import matplotlib.pyplot as plt
from math import exp, log
from scipy.stats import cauchy

def integral_1(x):
    return exp(x) * log(x)


def integral_2(x,y):
    return exp(- (x**2 * y**2)/2) * log(1 + (2*x - 3*y)**2)

def bounds():
    return [-np.inf, np.inf]


def calculate_first(n=1000):
    return calculate_integral(integral_1, cauchy.rvs(size=n), cauchy.pdf)

def calculate_integral(integrand, values, distr):
    return sum([integrand(el) / distr(el) for el in values]) / len(values)



def main():
    i1 = integrate.quad(integral_1, 1, 3)[0]
    print(i1)

    i2 = integrate.nquad(integral_2, [bounds(), bounds()])[0]
    print(i2)
    #print(calculate_first())
    return None


if __name__ == '__main__':
    main()
