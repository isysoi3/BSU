from math import sqrt, erf, exp, log10, log
from random import random


# Gauss

def get_next_standard_gauss():
    return sum([random() for _ in range(12)]) - 6


def get_next_gauss(m, s):
    return m + s * get_next_standard_gauss()


def gauss(m, s, n):
    for _ in range(n):
        yield get_next_gauss(m, s)


def gauss_distribution(x, m, s):
    return 0.5 * (1 + erf((x - m) / (sqrt(2) * s)))


# Lognormal

def get_next_lognormal(m, s):
    mu = log(m)
    general_gauss = get_next_gauss(mu, s)
    return exp(general_gauss)


def lognormal(m, s, n):
    for _ in range(n):
        yield get_next_lognormal(m, s)


def lognormal_distribution(x, m, s):
    if x == 0:
        x += 10 ** (-6)
    return 0.5 + 0.5 * erf((log(x) - log(m)) / (sqrt(2) * s))


# Logistic

def get_next_logistic(lg_a, lg_b):
    y = random()
    return lg_a + lg_b * log(y / (1 - y))


def logistic(n, lg_a, lg_b):
    for _ in range(n):
        yield get_next_logistic(lg_a, lg_b)


def logistic_distribution(x, lg_a, lg_b):
    return 1 / (1 + exp(-x - lg_a) / lg_b)
