from math import sqrt
import matplotlib.pyplot as plt

lambda_kolmogorova = 1.36
lambda_pears = 16.919
pieces = 11


def kolmogorov_test(N, n, m, s, distribution):
    max_delta = max([abs(fact_distribution(N, N[i], n) - distribution(N[i], m, s)) for i in range(n)])
    return sqrt(n) * max_delta <= lambda_kolmogorova


def fact_distribution(seq, x, n):
    return sum([1 if seq[i] < x else 0 for i in range(n)]) / n


def pearson_test(N, n, f, s, distr, build_gisto=False):
    hi = 0

    frequences = [0] * pieces
    step = abs(max(N) - min(N)) / pieces
    for i in range(0, n):
        index = int((N[i] - min(N)) / step)
        frequences[index if index < pieces else (pieces - 1)] += 1

    last_expected = 0

    if build_gisto:
        print(frequences)
        gisto(frequences)

    for i in range(0, pieces):
        if i != pieces - 1:
            fk = distr((i + 1) * step + min(N), f, s)
            fk1 = distr(i * step + min(N), f, s)
            p = fk - fk1
            last_expected += p
        else:
            p = 1 - last_expected
        hi += ((frequences[i] - n * p) ** 2) / (n * p)

    return hi <= lambda_pears

def gisto(s):
    x = range(len(s))
    ax = plt.gca()
    ax.bar(x, s, align='edge')
    ax.set_xticks(x)
    plt.show()