"""

Смоделировать дискретную случайную величину (задания на стр. 18-22). Исследовать точность моделирования.

1)	Осуществить моделирование n = 1000 реализаций СВ из заданных дискретных распределений.
2)	Вывести на экран несмещенные оценки математического ожидания и дисперсии, сравнить их с истинными значениями.
3)	Для каждой из случайных величин построить свой χ2-критерием Пирсона с уровнем значимость ε=0.05. Проверить, что вероятность ошибки I рода стремится к 0.05.
4)	Осуществить проверку каждой из сгенерированных выборок каждым из построенных критериев.

"""

from math import log10, ceil
from random import randrange
from math import factorial as fac


n = 1000


def distribution_info(name, distribution, math_exp, unbiased_estimate_math_exp, disp, unbiased_estimate_disp, p):
    print(name)
    print(distribution)
    print("МО: %f" % math_exp)
    print("Несмещенная оценка МО: %f" % unbiased_estimate_math_exp)
    print("Несмещенная оценка МО " + (">=" if unbiased_estimate_math_exp >= math_exp else "<") + " МО")
    print("Дисперсия: %f" % disp)
    print("Несмещенная оценка дисперсии: %f" % unbiased_estimate_disp)
    print("Несмещенная оценка дисперсии " + (">=" if unbiased_estimate_disp >= disp else "<") + " дисперсия")
    print("Тест Пирсона", pearson_test(p, distribution, 3,  5.99))


def generate(a0, b, m, n, c):
    for i in range(n):
        a0 = (b * a0 + c) % m
        yield a0 / m


def pearson_test(p, distr, k, delta):
    v = [0] * k
    for number in distr:
        if number < k:
            v[number] += 1

    hi = sum([(((v[i] - n * p(i)) ** 2) / (n * p(i))) for i in range(k)])

    print(hi)
    return hi < delta


def geometric_func(x):
    return 0.7 * ((1-0.7) ** (x-1))


def binomial(x, y):
    return fac(x) // fac(y) // fac(x - y)


def geometric_distribution(p):
    t = log10(1 - p)
    seq = list(generate(16387, 16387, 2 ** 31, n, 0))
    G = [ceil(log10(seq[i]) / t) for i in range(n)]
    math_exp_geom = 1 / p
    disp_geom = (1 - p) / p ** 2
    unbiased_estimate_math_exp_geom = sum(G, 0) / n
    unbiased_estimate_disp_geom = sum((G[i] - unbiased_estimate_math_exp_geom) ** 2 for i in range(n)) / (n - 1)

    distribution_info("---------- ГЕОМЕТРИЧЕСКОЕ РАСПРЕДЕЛЕНИЕ ----------",
                      G,
                      math_exp_geom,
                      unbiased_estimate_math_exp_geom,
                      disp_geom,
                      unbiased_estimate_disp_geom,
                      geometric_func)


def binomial_func(x):
    return binomial(6, x) * (0.75**x) * ((1-0.75) ** (6-x))


def binomial_distribution(p, m):
    a = [list(generate(16387, 16387, 2 ** 31, m, randrange(c ** c))) for c in range(n)]
    B = [(sum(1 if ((p - a[i][j]) > 0) else 0 for j in range(m))) for i in range(n)]
    unbiased_estimate_math_exp = sum(B) / n
    unbiased_estimate_disp_binom = sum((B[i] - unbiased_estimate_math_exp) ** 2 for i in range(n)) / (n - 1)

    distribution_info(name="---------- БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ  ----------",
                      distribution=B,
                      math_exp=m * p,
                      unbiased_estimate_math_exp=unbiased_estimate_math_exp,
                      disp=m * p * (1 - p),
                      unbiased_estimate_disp=unbiased_estimate_disp_binom,
                      p=binomial_func)


def main():
    p_binom = 0.75
    m = 6
    p_geom = 0.7
    geometric_distribution(p_geom)
    binomial_distribution(p_binom, m)


if __name__ == "__main__":
    main()
