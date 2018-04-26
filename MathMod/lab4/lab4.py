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
from math import exp, log, sqrt
from random import uniform


def integral_1(x):
    return exp(x) * log(x)


def integral_2(x, y):
    return exp(-(x**2 + y**2)/2) * log(1 + (2*x - 3*y)**2)


def bounds():
    return [-np.inf, np.inf]


def calculate_integral(integrand, a, b, n=1000):
    return sum([integrand(uniform(a, b)) for _ in range(n)]) * (b - a) / n


def calculate_first(n=1000):
    return calculate_integral(integral_1, 1, 3, n)


def second_f(args):
    return integral_2(*args)


def uniform_pdf(x):
    return 1/30 if -15 <= x <= 15 else 0


def distr(args):
    x, y = args
    return uniform_pdf(x) * uniform_pdf(y)


def calculate_second(n=1000):
    x = [uniform(-15, 15) for _ in range(n)]
    y = [uniform(-15, 15) for _ in range(n)]
    return calculate_integral_inf(second_f, list(zip(x, y)), distr)


def calculate_integral_inf(integrand, values, distr):
    return sum([integrand(el) / distr(el) for el in values]) / len(values)


def print_info(mk, math):
    print("Значение по Монте-Карло", mk,
          "\nПриближенное, полученное в математическом пакете", math)


def get_numbers():
    return (2**x for x in range(16))


def test(func):
    m = 10
    return [sum([func(n) for _ in range(m)]) / m for n in get_numbers()]


def draw(real, theory):
    rc('ytick', labelsize=15)
    rc('xtick', labelsize=15)
    plt.figure(figsize=(20, 8))
    x = list(get_numbers())
    plt.plot(x, [theory]*len(x), label='theory')
    plt.xscale('log')
    plt.plot(x, real, label='real')
    plt.xticks(x, x)
    plt.xlabel('n - number of iterations', fontsize=20)
    plt.ylabel('integral value', fontsize=20)
    plt.legend()
    plt.show()


def show_plots(i1, i2):
    i1_real = test(calculate_first)
    i2_real = test(calculate_second)
    draw(i1_real, i1)
    draw(i2_real, i2)


def main():
    i1 = integrate.quad(integral_1, 1, 3)[0]
    i1_test = calculate_first()
    print_info(i1_test, i1)

    i2 = integrate.nquad(integral_2, [bounds(), bounds()])[0]
    i2_test = calculate_second()
    print_info(i2_test, i2)

    show_plots(i1, i2)


def main1():

    print("Enter numbers from 1 to 5")
    listString = input()
    list = [int(item, base=10) for item in listString.split(" ")]

    aver = sum([el * (index + 1) for index, el in enumerate(list)]) / sum(list)

    stdev = sqrt(sum([(el - aver) ** 2 for el in range(1, 6)]) / (len(list) - 1))

    print("Av =", aver)
    print("STDEV = ", stdev)

    x = np.arange(len(list))
    plt.bar([1,2,3,4,5], height=list)
    plt.xticks([1,2,3,4,5], [1,2,3,4,5])
    plt.plot([0] + list,'r-',color="red",)
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main1()

#2 5 6 7 8