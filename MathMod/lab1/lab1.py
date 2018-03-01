import math

def kolmogorov_test(seq):
    k = 1000
    delta = 1.36
    sup = 0
    n = len(seq)
    for i in range(0, k):
        hits = 0
        for j in range(0, n):
            if seq[j] <= i / k:
                hits += 1
        F = hits / n
        if sup < abs(F - i / k):
            sup = abs(F - i / k)
    return math.sqrt(n) * sup < delta

def pirson_test(seq):
    k = 20
    n = len(seq)
    delta = 30.1
    psi = 0
    counting = [0] * k
    for i in range(0, n):
        num = int(seq[i] * k)
        counting[num] += 1
    for i in range(0, k):
        tmp = n / k
        psi += ((counting[i] - tmp) ** 2) / tmp
    return psi < delta

def maclaren_marsaglia(k, n, b, c ):
    v = [None] * n
    a = [None] * n
    for t in range(0, k):
        v[t] = b[t]

    for i in range(0, n - k):
        s = int(c[i] * k)
        a[i] = v[s]
        v[s] = b[i + k]

    for i in range(n - k, n):
        a[i] = b[i]
    return a

def main():
    a0 = b0 = 29791
    y = 4
    m = 2 ** 31
    f = 5
    n = 1000
    k = 128
    b = [a0 / m]
    c = [a0 / m]

    for t in range(1, n):
        b.append(((b[t - 1] * b0 * m) % m) / m)
        tmp = c[t - 1] * m
        c.append((((tmp ** 2) * y + tmp * b0 + f) % m) / m)

    a = maclaren_marsaglia(k, n ,b, c)

    with open('out.txt', 'w') as f:
        print("Конгруэнтный метод: " , b,file=f)
        print("Метод Макларена–Марсаль: ", a, file=f)
        print("Тест Пирсона для конгруэнтого метода", pirson_test(b), file=f)
        print("Тест Пирсона для метод Макларена–Марсальи", pirson_test(a), file=f)
        print("Тест Колмогорова для конгруэнтого метода", kolmogorov_test(b), file=f)
        print("Тест Колмогорова для метод Макларена–Марсальи", kolmogorov_test(a), file=f)

if __name__ == "__main__":
    main()