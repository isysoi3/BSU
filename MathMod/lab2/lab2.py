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


n = 10
p_binom = 0.25
m = 2
p_geom = 0.7
DELTA = {
    2: 3.841,
    3: 5.991,
    4: 7.815,
    5: 9.488,
    6: 11.070,
    7: 12.592,
    8: 14.067,
    9: 15.507,
    10: 16.919,
    11: 18.307,
    12: 19.675,
    13: 21.026,
    14: 22.362,
    15: 23.685,
    16: 24.996,
    17: 26.296,
    18: 27.587,
    19: 28.869,
    20: 30.144,
    21: 31.410,
    22: 32.671,
    23: 33.924,
    24: 35.172,
    25: 36.415,
    26: 37.652,
    27: 38.885,
    28: 40.113,
    29: 41.337,
    30: 42.557
}


def distribution_info(name, distribution, math_exp, unbiased_estimate_math_exp, disp, unbiased_estimate_disp, p, start):
    print(name)
    print(distribution)
    print("МО: %f" % math_exp)
    print("Несмещенная оценка МО: %f" % unbiased_estimate_math_exp)
    print("Несмещенная оценка МО " + (">=" if unbiased_estimate_math_exp >= math_exp else "<") + " МО")
    print("Дисперсия: %f" % disp)
    print("Несмещенная оценка дисперсии: %f" % unbiased_estimate_disp)
    print("Несмещенная оценка дисперсии " + (">=" if unbiased_estimate_disp >= disp else "<") + " дисперсия")
    print("Критерий Пирсона", pearson_test(p, distribution, start))
    print()


def generate(a0, b, m, n, c):
    for i in range(n):
        a0 = (b * a0 + c) % m
        yield a0 / m


def frequences(seq):
    t = max(seq)
    v = [0] * (t + 1)

    for element in seq:
        v[element] += 1

    return v, t, DELTA[t]


def pearson_test(p, distr, start):
    v, k, delta = frequences(distr)

    hi = sum([(((v[i] - n * p(i)) ** 2) / (n * p(i))) for i in range(start, k)])

    return hi < delta


def geometric_func(x):
    return p_geom * ((1-p_geom) ** (x-1))


def binomial(x, y):
    return fac(x) // fac(y) // fac(x - y)


def geometric_distribution(p, isPrinting):
    t = log10(1 - p)
    seq = list(generate(16387, 16387, 2 ** 31, n, randrange(0,1000)))
    G = [ceil(log10(a) / t) for a in seq]

    if isPrinting:
        unbiased_estimate_math_exp_geom = sum(G, 0) / n
        unbiased_estimate_disp_geom = sum((g - unbiased_estimate_math_exp_geom) ** 2 for g in G) / (n - 1)
        distribution_info(name="************** ГЕОМЕТРИЧЕСКОЕ РАСПРЕДЕЛЕНИЕ **************",
                          distribution=G,
                          math_exp=1 / p,
                          unbiased_estimate_math_exp=unbiased_estimate_math_exp_geom,
                          disp=(1 - p) / p ** 2,
                          unbiased_estimate_disp=unbiased_estimate_disp_geom,
                          p=geometric_func,
                          start=1)
    return G


def binomial_func(x):
    return binomial(m, x) * (p_binom**x) * ((1-p_binom) ** (m-x))


def binomial_distribution(p, m, isPrinting):
    a = [list(generate(16387, 16387, 2 ** 31, m, randrange(c ** c))) for c in range(n)]
    B = [(sum(1 if ((p - a[i][j]) > 0) else 0 for j in range(m))) for i in range(n)]

    if isPrinting:
        unbiased_estimate_math_exp = sum(B) / n
        unbiased_estimate_disp_binom = sum((b - unbiased_estimate_math_exp) ** 2 for b in B) / (n - 1)
        distribution_info(name="************** БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ **************",
                          distribution=B,
                          math_exp=m * p,
                          unbiased_estimate_math_exp=unbiased_estimate_math_exp,
                          disp=m * p * (1 - p),
                          unbiased_estimate_disp=unbiased_estimate_disp_binom,
                          p=binomial_func,
                          start=0)
    return B


def main():
    geometric_distribution(p_geom, True)
    binomial_distribution(p_binom, m, True)

    geom = 0
    binom = 0

    t = 1000
    for _ in range(t):
        binom += 0 if pearson_test(binomial_func, binomial_distribution(p_binom, m, False), 1) else 1
        geom += 0 if pearson_test(geometric_func, geometric_distribution(p_geom, False), 1) else 1

    print("Вероятность ошибки первого рода в биноминальном распределении ",  binom/t)
    print("Вероятность ошибки первого рода в геометр распределении ", geom/t)


if __name__ == "__main__":
    main()
