# Используя метод Маклерена-Марсальи построить датчик БСВ (1 датчик должен быть мультипликативно конгруентный, второй – на выбор). Исследовать точность построенной БСВ.
#   1) Осуществить моделирование n = 1000 реализаций БСВ с помощью мультипликативного конгруэнтного метода (МКМ) с параметрами a0, β, M = 231 .
#  2) Осуществить моделирование n = 1000 реализаций БСВ с помощью метода Макларена-Марсальи (один датчик должен быть мультипликативно конгруентный (п. 1), второй – на выбор).#K – объем вспомогательной таблицы.
#  3) Проверить точность моделирования обоих датчиков (п. 1 и п. 2) с помощью критерия согласия Колмогорова и χ2-критерия Пирсона с уровнем значимости ε = 0.05.
double
F = (double)
hits / X;
// std::cout << abs(F - (double)
i / L) << std::endl;
if (sup < abs(F - (double)i / L))
sup = abs(F - (double)
i / L);
}

if (sqrt(X) * sup < C)
    return true;
return false;
import math
def kolgomorov_test( X,  L, func,  C):
    sup = 0
    for i in range(0, L):
        hits = 0
        for j in range(0, X):
            if (func < i/L) :
                hits += 1
            f
    return True if math.sqrt(X)* sup < c else False

def pirson_test( X,  L, func,  C):
    div = [0] *  L
    hi = 0
    for i in range(0,X):
        div[int(func() * L)] += 1
    for i in range(0,L):
        hi += ((div[i] - X/L) ** 2) / X/L
    return True if hi < c else False

a00 = b0 = 29791
a01 = b1 = 16395
m = 2 ** 31
n = 1000
k = 128
b = [(((a00 * b0) % m) / m)]
c = [(((a01 * b1) % m) / m)]
a = [None] * n
v = [None] * n

for t in range(1, n):
    b.append(((b[t - 1] * b0 * m) % m) / m)
    c.append(((c[t - 1] * b1 * m) % m) / m)

for i in range(0, k-1):
    v[i] = b[i]

for t in range(0, n):
    a[t] = v[int(c[t] * k)]

for i in range(k, n):
    v[i] = b[i]

for t in range(1, n):
    print(v[t])

print(pirson_test(1000, 25, test(), 37.65))