import math

a0 = b0 = 16387
y = 4
m = 2 ** 31
f = 5
n = 1000
k = 48
b = [a0/m]
c = [a0/m]
a = [None] * n
v = [None] * n


def kolmogorov_test(seq,n):
    k = 30
    delta = 0.24
    sup = 0
    for i in range(0, k):
        hits = 0
        for j in range(0,n):
            if seq[j] < i/k:
                hits += 1
        F = hits/n
        if sup < abs(F - i/k):
            sup = abs(F - i/k)
    print(math.sqrt(n) * sup)
    return True if math.sqrt(n) * sup < delta else False



def pirson_test(seq,n):
    k = 13
    delta = 21.0
    hi = 0
    counting = [0] * k
    for i in range(0, n):
        num = int(seq[i] * k)
        counting[num] += 1
    for i in range(0,k):
        tmp = n/k
        hi += ((counting[i] - tmp) ** 2) / (tmp)
    return True if hi < delta else False


for t in range(1, n):
    b.append(((b[t - 1] * b0 * m) % m) / m)
    buf = c[t - 1] * m
    c.append(((buf ** 2 * y + buf * b0 + f) % m) / m)

for t in range(0, k):
    v[t] = b[t]

for i in range(0, n - k):
    s = int(c[i] * k)
    a[i] = v[s]
    v[s] = b[i+k]

for i in range(n-k, n):
    a[i] = b[i]

print(b)
print(c)

print(pirson_test(b,n),pirson_test(a,n))

print(kolmogorov_test(b,n),kolmogorov_test(a,n))

print(a)

