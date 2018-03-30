"""
    1) Осуществить моделирование n = 1000 реализаций СВ из нормального закона распределения N(m, s2) с заданными параметрами. Вычислить несмещенные оценки математического ожидания и дисперсии, сравнить их с истинными.
    2) Смоделировать n = 1000 СВ из заданных абсолютно непрерывных распределений. Вычислить несмещенные оценки математического ожидания и дисперсии, сравнить их с истинными значениями (если это возможно).
    3)Для каждой из случайных величин построить свой критерий Колмогорова с уровнем значимость ε=0.05. Проверить, что вероятность ошибки I рода стремится к 0.05.
    4) Для каждой из случайных величин построить свой χ2-критерий Пирсона с уровнем значимость ε=0.05. Проверить, что вероятность ошибки I рода стремится к 0.05.
    5)Осуществить проверку каждой из сгенерированных выборок каждым из построенных критериев.
"""

from math import pi, exp
import generators
from tests import *


def print_info(name, distribution, math_exp, unbiased_est_math_exp, disp, unbiased_est_disp):
    print(name)
    print(distribution)
    print("Истинное МО:", math_exp)
    print("Несмещенная оценка МО:", unbiased_est_math_exp)
    print("Несмещенная оценка МО " + ("больше" if unbiased_est_math_exp > math_exp else "меньше") + " истинного МО")
    print("Истинная дисперсия:", disp)
    print("Несмещенная оценка дисперсии:", unbiased_est_disp)
    print(
        "Несмещенная оценка дисперсии " + ("больше" if unbiased_est_disp > disp else "меньше") + " истинной дисперсии")


def gauss_distribution(n, m, s2, is_printing_info=False, kolm_test=False, pears_test=False):
    s = sqrt(s2)
    gauss = list(generators.gauss(m=m, n=n, s=s))
    unbiased_est_math_exp = sum(gauss) / n
    unbiased_est_disp = sum((gauss[i] - unbiased_est_math_exp) ** 2 for i in range(n)) / (n - 1)

    if is_printing_info:
        print_info("____________ НОРМАЛЬНОЕ РАСПРЕДЕЛЕНИЕ ____________",
                   gauss,
                   m,
                   unbiased_est_math_exp,
                   s2,
                   unbiased_est_disp)

    if kolm_test:
        print("Критерий Колмогорова:", kolmogorov_test(
            gauss,
            n,
            m,
            s,
            generators.gauss_distribution))

    if pears_test:
        print("Критерий Пирсона:", pearson_test(gauss,
                                                n,
                                                m,
                                                s,
                                                generators.gauss_distribution,
                                                True))

    return gauss


def lognormal_distribution(n, m, s2, is_printing_info=False, kolm_test=False, pears_test=False):
    s = sqrt(s2)
    lognormal = list(generators.lognormal(m=m, n=n, s=s))
    math_exp = exp(m + s2 / 2)
    unbiased_est_math_exp = sum(lognormal) / n
    disp = (exp(s2) - 1) * exp(2 * m + s2)
    unbiased_est_disp = sum((lognormal[i] - unbiased_est_math_exp) ** 2 for i in range(n)) / (n - 1)

    if is_printing_info:
        print_info("____________ ЛОГОНОРМАЛЬНОЕ  РАСПРЕДЕЛЕНИЕ ____________",
                   lognormal,
                   math_exp,
                   unbiased_est_math_exp,
                   disp,
                   unbiased_est_disp)

    if kolm_test:
        print("Критерий Колмогорова:", kolmogorov_test(
            lognormal,
            n,
            m,
            s,
            generators.lognormal_distribution))

    if pears_test:
        print("Критерий Пирсона:", pearson_test(lognormal,
                                                n,
                                                m,
                                                s,
                                                generators.lognormal_distribution,
                                                True))

    return lognormal


def logistic_distribution(n, lg_a, lg_b, is_printing_info=False, kolm_test=False, pears_test=False):
    lg = list(generators.logistic(n, lg_a, lg_b))
    math_exp = lg_a
    unbiased_est_math_exp = sum(lg) / n
    disp = (pi ** 2 / 3) * (lg_b ** 2)
    unbiased_est_disp = sum((lg[i] - unbiased_est_math_exp) ** 2 for i in range(n)) / (n - 1)

    if is_printing_info:
        print_info("\n____________ ЛОГИСТИЧЕСКОЕ РАСПРЕДЕЛЕНИЕ ____________",
                   lg,
                   math_exp,
                   unbiased_est_math_exp,
                   disp,
                   unbiased_est_disp)

    if kolm_test:
        print("Критерий Колмогорова:", kolmogorov_test(lg,
                                                       n,
                                                       lg_a,
                                                       lg_b,
                                                       generators.logistic_distribution))

    if pears_test:
        print("Критерий Пирсона:", pearson_test(lg,
                                                n,
                                                lg_a,
                                                lg_b,
                                                generators.logistic_distribution,
                                                True))

    return lg




def main():
    n = 1000
    m = 0
    s2 = 16
    ln_m = 2
    ln_s2 = 16
    lg_a = 1
    lg_b = 1
    gauss_distribution(n, m, s2, True, True, True)
    lognormal_distribution(n, ln_m, ln_s2, True, True, True)
    logistic_distribution(n, lg_a, lg_b, True, True, True)

    tests = 2

    count_kolm_gauss = 0
    count_kolm_lognorma = 0
    count_kolm__logist = 0

    count_pears_gauss = 0
    count_pears_lognorma = 0
    count_pears_logist = 0

    for i in range(tests):
        gauss = gauss_distribution(n, m, s2)
        count_kolm_gauss += 0 if kolmogorov_test(gauss, n, m, sqrt(s2), generators.gauss_distribution) else 1
        count_pears_gauss += 0 if pearson_test(gauss, n, m, sqrt(s2), generators.gauss_distribution) else 1

        lognormal = lognormal_distribution(n, ln_m, ln_s2)
        count_kolm_lognorma += 0 if kolmogorov_test(lognormal, n, ln_m, sqrt(ln_s2),
                                                    generators.lognormal_distribution) else 1
        count_pears_lognorma += 0 if pearson_test(lognormal, n, ln_m, sqrt(ln_s2),
                                                  generators.lognormal_distribution) else 1

        logistic = logistic_distribution(n, lg_a, lg_b)
        count_kolm__logist += 0 if kolmogorov_test(logistic, n, lg_a, lg_b,
                                                   generators.logistic_distribution) else 1
        count_pears_logist += 0 if pearson_test(logistic, n, lg_a, lg_b,
                                                generators.logistic_distribution) else 1
    if tests != 0:
        print("\nВероятность ошибки I рода критерия Колмогорова для нормального распределения:",
              count_kolm_gauss / tests)
        print("Вероятность ошибки I рода критерия Пирсона для нормального распределения:",
              count_pears_gauss / tests)

        print("\nВероятность ошибки I рода критерия Колмогорова для логонормального распределения:",
              count_kolm_lognorma / tests)
        print("Вероятность ошибки I рода критерия Пирсона для логонормального распределения:",
              count_pears_lognorma / tests)

        print("\nВероятность ошибки I рода критерия Колмогорова для логистического распределения:",
              count_kolm__logist / tests)
        print("Вероятность ошибки I рода критерия Пирсона для логистического распределения:",
              count_pears_logist / tests)


if __name__ == '__main__':
    main()
