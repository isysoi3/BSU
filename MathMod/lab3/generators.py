from math import sqrt, erf, log, exp
from random import random


# Gauss

def get_next_standard_gauss():
    return sum([random() for _ in range(12)]) - 6


def get_next_gauss(m, s):
    return m + s * get_next_standard_gauss()


def gauss(m, s, n):
    """
    N(m, s^2)
        :param m: mean
        :param s: dispersion
        :param n: size
    """
    for _ in range(n):
        yield get_next_gauss(m, s)


def gauss_distribution(m, s, x):
    return 0.5 * (1 + erf((x - m) / (sqrt(2) * s)))


# Lognormal

def get_next_lognormal(m, s):
    mu = log(m)
    general_gauss = get_next_gauss(mu, s)
    return exp(general_gauss)


def lognormal(m, s, n):
    """
    Lognormal(m, s^2)
        :param m: mean
        :param s: dispersion
        :param n: size
    """
    for _ in range(n):
        yield get_next_lognormal(m, s)


def lognormal_distribution(m, s, x):
    if x == 0:
        x += 10 ** (-6)
    return 0.5 + 0.5 * erf((log(x) - log(m)) / (sqrt(2) * s))


# Logistic

def get_next_logistic():
    return None


def logistic(lmbda, n):
    for _ in range(n):
        yield get_next_logistic()
