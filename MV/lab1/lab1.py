import numpy as np
from numpy import random as rand
import random
import time
import math


def swap_cols(matrix, first, second):
    matrix[:, [first, second]] = matrix[:, [second, first]]


def print_matrix(matrix):
    print("---------------------------------------")
    for line in matrix:
        print(line)
    print("---------------------------------------")


def inverse_matrix(A):
    n = len(A)
    matrix = np.copy(np.hstack((A, np.identity(n))))

    for i in range(n):
        matrix[i] /= matrix[i][i]
        for j in range(i + 1, n):
            matrix[j] -= matrix[i] * matrix[j][i]

    for i in range(n - 1, -1, -1):
        for j in range(i - 1, -1, -1):
            matrix[j] -= matrix[i] * matrix[j][i]

    return matrix[:, n:]


def l_norm(matrix):
    return max(np.sum(np.absolute(matrix), axis=1))


def condition_number(A):
    return l_norm(A) * l_norm(inverse_matrix(A))


def generate_matrix(size, n, simple_random=False):
    matrix = np.zeros((size, size))
    y = np.zeros(size)
    for i in range(0, size):
        y[i] = random.randrange(-10, 10) if simple_random else ((2 ** n) * 2) * rand.random_sample() - (2 ** n)  #
        for j in range(i + 1, size):
            matrix[i][j] = matrix[j][i] = random.randrange(-10, 10) if simple_random else ((
                                                                                                   2 ** n) * 2) * rand.random_sample() - (
                                                                                                  2 ** n)

    row, col = np.diag_indices_from(matrix)
    matrix[row, col] = np.absolute(matrix).sum(axis=1)
    return matrix, y, matrix.dot(y)


def sor(A, b_, w, eps=10e-13):
    n = len(A)
    matrix = A.copy()
    b = b_.copy()
    x = np.zeros(n)
    x1 = np.zeros(n)
    while (True):
        for i in range(n):
            x[i] = (1 - w) * x[i] + \
                   w / matrix[i][i] * (b[i]
                                       - sum([matrix[i][j] * x[j] for j in range(i)])
                                       - sum([matrix[i][j] * x[j] for j in range(i + 1, n)]))
        if np.linalg.norm(x - x1) < eps:
            return x
        x1 = x.copy()


def max_norm_of_vectors(vector, y):
    return max([abs(vector[i] - y[i]) for i in range(len(y))])


def gauus_by_row(A, b_):
    matrix = np.copy(np.hstack((A, b_[:, None])))
    n = len(A)

    for i in range(n):
        matrix[i] /= matrix[i][i]
        max = abs(matrix[i][i])
        max_index = i
        for k in range(i + 1, n):
            if abs(matrix[i][k]) > max:
                max = abs(matrix[i][k])
                max_index = k
        swap_cols(matrix, i, max_index)
        for j in range(i + 1, n):
            matrix[j] -= matrix[i] * matrix[j][i]

    for i in range(n - 1, -1, -1):
        for j in range(i - 1, -1, -1):
            matrix[j] -= matrix[i] * matrix[j][i]

    return matrix[:, -1]


def lu_decomposition(A):
    matrix = A.copy()
    n = len(matrix)

    for i in range(n):
        for j in range(i + 1, n):
            multiplier = matrix[j][i] / matrix[i][i]
            matrix[j][i:] -= matrix[i][i:] * multiplier
            matrix[j][i] = multiplier

    U = np.zeros((n, n))
    L = np.identity(n)

    for i in range(n):
        for j in range(i, n):
            U[i][j] = matrix[i][j]

    for i in range(1, n):
        for j in range(i):
            L[i][j] = matrix[i][j]

    return L, U


def reversal_gauus(A, b):
    n = len(A)
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        tmp_x = b[i]
        for g in range(i + 1, n):
            tmp_x -= A[i][g] * x[g]
        x[i] = tmp_x / A[i][i]

    return x


def gauus(A, b_):
    matrix = np.copy(np.hstack((A, b_[:, None])))
    n = len(A)

    for i in range(n):
        matrix[i] /= matrix[i][i]
        for j in range(i + 1, n):
            matrix[j] -= matrix[i] * matrix[j][i]

    for i in range(n - 1, -1, -1):
        for j in range(i - 1, -1, -1):
            matrix[j] -= matrix[i] * matrix[j][i]

    return matrix[:, -1]


def solve_lu(lower_triangular, upper_triangular, b_):
    L = lower_triangular.copy()
    U = upper_triangular.copy()
    b = b_.copy()
    n = len(L)
    y = np.zeros(n)

    for i in range(n):
        y[i] = b[i] - sum([L[i][g] * y[g] for g in range(i - 1, -1, -1)])

    return reversal_gauus(U, y)


def cholesky_decomposition(A, b_):
    matrix = np.copy(np.hstack((A, b_[:, None])))
    n = len(A)

    for i in range(n):
        matrix[i] /= matrix[i][i]
        for j in range(i + 1, n):
            matrix[j][i:] -= matrix[i][i:] * matrix[j][i]

    return reversal_gauus(matrix[:, :n], matrix[:, -1])


def test_all(n, size, number_of_repeats, isEasy):
    conditions = []
    inverse_times = []
    gauus_times = []
    gauus_norm = []
    lu_decomposition_times = []
    lu_solve_times = []
    lu_norm = []
    cholesky_decomposition_times = []
    cholesky_norm = []
    sor_times = []
    sor_norm = []

    for i in range(number_of_repeats):
        print("________________" + str(i + 1) + " iteration________________")

        matrixA, y, b = generate_matrix(size=size, n=n, simple_random=isEasy)
        start_time = time.time()
        conditions.append(condition_number(matrixA))
        inverse_times.append(time.time() - start_time)
        print("Condition of matrix ", conditions[-1])

        start_time = time.time()
        rez = gauus_by_row(matrixA, b)
        gauus_times.append(time.time() - start_time)
        gauus_norm.append(max_norm_of_vectors(rez, y))
        print("Gauus by row", np.allclose(rez, y))

        start_time = time.time()
        L, U = lu_decomposition(matrixA)
        lu_decomposition_times.append(time.time() - start_time)

        start_time = time.time()
        rez = solve_lu(L, U, b)
        lu_solve_times.append(time.time() - start_time)
        lu_norm.append(max_norm_of_vectors(rez, y))
        print("LU answer", np.allclose(rez, y))

        start_time = time.time()
        rez = cholesky_decomposition(matrixA, b)
        cholesky_decomposition_times.append(time.time() - start_time)
        cholesky_norm.append(max_norm_of_vectors(rez, y))
        print("Cholesky answer", np.allclose(rez, y))

        start_time = time.time()
        rez = sor(matrixA, b, (n + 1) / 6)
        sor_times.append(time.time() - start_time)
        sor_norm.append(max_norm_of_vectors(rez, y))
        print("SOR answer", np.allclose(rez, y))

    print("Average conditional number: ", sum(conditions) / number_of_repeats, file=f)
    print("Max and min conditional number: ", max(conditions), min(conditions), file=f)
    print(file=f)

    print("Average search time for inverse matrix in sec: ", sum(inverse_times) / number_of_repeats, file=f)
    print(file=f)

    print("Average time for gauus solving in sec: ", sum(gauus_times) / number_of_repeats, file=f)
    print("Average gauus norm: ", sum(gauus_norm) / number_of_repeats, file=f)
    print("Max and min gauus norm: ", max(gauus_norm), min(gauus_norm), file=f)
    print(file=f)

    print("Average time for lup decomposition in sec: ", sum(lu_decomposition_times) / number_of_repeats, file=f)
    print("Average time for lu solving in sec: ", sum(lu_solve_times) / number_of_repeats, file=f)
    print("Average lu norm: ", sum(lu_norm) / number_of_repeats, file=f)
    print("Max and min lu norm ", max(lu_norm), min(lu_norm), file=f)
    print(file=f)

    print("Average time for solving cholesky decomposition in sec: ",
          sum(cholesky_decomposition_times) / number_of_repeats,
          file=f)
    print("Average cholesky norm: ", sum(cholesky_norm) / number_of_repeats, file=f)
    print("Max and min cholesky norm: ", max(cholesky_norm), min(cholesky_norm), file=f)
    print(file=f)

    print("Average time of SOR in sec: ", sum(sor_times) / number_of_repeats, file=f)
    print("Average SOR norm: ", sum(sor_norm) / number_of_repeats, file=f)
    print("Max and min SOR norm: ", max(sor_norm), min(sor_norm), file=f)


def danilevsky_method(A, b_):
    n = len(A)
    matrix = A.copy()
    for i in range(n - 1, 0, -1):
        c = matrix[i, i - 1]
        matrix[:, i - 1] /= c
        matrix[i - 1] *= c
        for j in range(n):
            if j != (i - 1):
                c = matrix[i, j]
                matrix[:, j] -= c * matrix[:, i - 1]
                matrix[i - 1] += c * matrix[j]
    if n % 2 == 0:
        p = build_characteristic_polynomial(np.append([1], -matrix[0]))
    else:
        p = build_characteristic_polynomial(np.append([-1], matrix[0]))
    newton_method(p)

def build_characteristic_polynomial(coef):
    return np.poly1d(coef)


def newton_method(f):
    print(f)
    fix = f.deriv()
    roots = np.roots(f)
    roots.sort()
    print(roots)
    interval = int(roots.max()) + 5
    new_roots = []
    for i in np.arange(-interval, interval, 0.001):
        if f(i) * f(i + 0.001) <= 0:
            root = newton_method_with_fix_derivative(f, fix(i), i)
            if root is None:
                root = newton_method_with_fix_derivative(f, fix(i + 0.001), i + 0.001)
                new_roots.append(root)
            else:
                new_roots.append(root)
    print(np.allclose(new_roots, roots))


def newton_method_with_fix_derivative(f, u, root):
    x = root
    if f(x) * f.deriv().deriv()(root) <= 0:
        return None
    while True:
        if np.isclose(f(x), 0):
            return x
        x = x - f(x) / u


def strpen_method(A, b_):
    print_matrix(A)
    rez = np.linalg.eigvals(A)
    print(rez)
    print()

    u1, l1 = test(A, 1, 0)
    u2, l2 = test1(A, -1, l1)
    u3, l3 = test1(A, l2*3, -l1)
    print(l1, l2, l3)

    '''
     for _ in range(n):
    #while np.linalg.norm(matrix.dot(u) - l * u) > 10e-5:
        v = matrix.dot(u)
        u - maNtrix.dot(v)
        l = np.sqrt(v.max())
        v = l*v + u
        u /= u.max()
        v /= v.max()
    '''


def test(A, alpha, beta):
    matrix = A.copy()
    n = len(matrix)
    l = 0
    b = alpha * matrix + np.diag([beta for _ in range(n)])
    u = np.zeros(n)
    old_u = np.zeros(n)
    u[0] = 1
    while True:
        v = b.dot(u)
        l = np.max(abs(v))
        u = v / l
        if np.linalg.norm(u - old_u) < 10e-5:
            break
        old_u = u
    return u, (l - beta) / alpha

def test1(A, alpha, beta):
    matrix = A.copy()
    n = len(matrix)
    l = 0
    b = alpha * matrix + np.diag([beta for _ in range(n)])
    u = np.zeros(n)
    old_u = np.zeros(n)
    u[0] = 1
    while True:
        v = b.dot(u)
        u = b.dot(v)
        l = np.sqrt(np.max(abs(u)))
        v = l * v + u
        u /= max(abs(u))
        v /= max(abs(v))
        if np.linalg.norm(u - old_u) < 10e-5:
            break
        old_u = u
    return u, ((l - beta) / alpha)


def qr_decomposition(A):
    n = len(A)
    Q = np.identity(n)
    R = np.copy(A)

    (rows, cols) = np.tril_indices(n, -1, n)
    for row, col in zip(rows, cols):
        c, s = get_sin_cos_numbers(R[col, col], R[row, col])
        G = get_rotation_matrix(n=n, c=c, s=s, row=row, col=col)

        R = G.dot(R)
        Q = Q.dot(G.transpose())

    return Q, R


def get_sin_cos_numbers(a, b):
    r = math.hypot(a, b)
    c = a/r
    s = -b/r

    return c, s


def get_rotation_matrix(c, s, n, row, col):
    T = np.identity(n)
    T[col, row] = T[col, row] = c
    T[row, col] = s
    T[col, row] = -s
    return T


def main(f, isEasy, number_of_repeats):
    precision = 5 if isEasy else 13
    size = 256 if isEasy else 256
    sizeB = 10
    n = 7

    np.set_printoptions(precision=precision)
    # test_all(n, size, number_of_repeats,isEasy)
    matrixA, y, b = generate_matrix(size=size, n=n, simple_random=isEasy)
    matrixB = matrixA[:sizeB, len(matrixA) - sizeB:]
    #matrixB = matrixA[:sizeB, :sizeB]
    print_matrix(matrixB)
    danilevsky_method(matrixB, b)
   # strpen_method(matrixB, b)
    #Q, R = qr_decomposition(matrixB)


if __name__ == '__main__':
    f = open("out.txt", mode="w")
    main(f=f, isEasy=True, number_of_repeats=5)
