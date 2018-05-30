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
        matrix[i] /= matrix[i,i]
        for j in range(i + 1, n):
            matrix[j] -= matrix[i] * matrix[j,i]

    for i in range(n - 1, -1, -1):
        for j in range(i - 1, -1, -1):
            matrix[j] -= matrix[i] * matrix[j,i]

    return matrix[:, n:]


def l_norm(matrix):
    return max(np.sum(np.absolute(matrix), axis=1))


def condition_number(A):
    return l_norm(A) * l_norm(inverse_matrix(A))


def generate_matrix(size, n, simple_random=False):
    matrix = np.zeros((size, size))
    y = np.zeros(size)
    max_generate_number = (2 ** (n/4))
    for i in range(0, size):
        y[i] = random.randrange(-10, 10) if simple_random else (max_generate_number * 2) * rand.random_sample() - (max_generate_number)  #
        for j in range(i + 1, size):
            matrix[i][j] = matrix[j][i] = random.randrange(-10, 10) if simple_random else (max_generate_number * 2) * rand.random_sample() - (max_generate_number)

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
                                       - sum(matrix[i,:i] * x[:i])
                                       - sum(matrix[i,i+1:] * x[i+1:]))
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
            tmp_x -= A[i,g] * x[g]
        x[i] = tmp_x / A[i,i]

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


def method_square_root(A, b_):
    matrix = np.copy(np.hstack((A, b_[:, None])))
    n = len(A)

    for i in range(n):
        matrix[i] /= matrix[i,i]
        for j in range(i + 1, n):
            matrix[j,j:] -= matrix[i,j:] * matrix[j,i]
            matrix[j:,j] = matrix[j,j:n]

    return reversal_gauus(matrix[:, :n], matrix[:, -1])


def danilevsky_method(A):
    n = len(A)
    matrix = danilevsky_transformation(A)

    coef = np.append([1], -matrix[0]) * ((-1)**n)

    p = build_characteristic_polynomial(coef)
    a = max(abs(coef))
    k= np.where(abs(coef)==a)
    newton_method(p, a, k[0][0])


def danilevsky_transformation(A):
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
    return matrix

def build_characteristic_polynomial(coef):
    return np.poly1d(coef)


def newton_method(f,a,k):
    print(f)
    fix = f.deriv()
    roots = np.roots(f)

    interval = math.ceil(a ** (1/k))
    print(interval)
    new_roots = []
    step = 0.1
    for i in np.arange(-1-interval, 1+interval, step):
        if f(i) * f(i + step) <= 0:
            root = newton_method_with_fix_derivative(f, fix(i), i)
            if root is None:
                continue
            else:
                new_roots.append(root)

    print(roots)
    print(new_roots)



def newton_method_with_fix_derivative(f, u, root):
    x = root
    i = 0
    if f(x) * (f.deriv().deriv()(root)) <= 0:
        return None
    while True:
        if f(x) < 10e-6:
            return x
        if i > 10000:
            return None
        x = x - f(x) / u
        i += 1


def stepen_method(A):
    u1, l1 = find_lambda_with_vector(A, 1, 0)
    u2, l2 = find_lambda_with_vector(A, -1, l1)
    print(l1, l2)


def find_lambda_with_vector(A, alpha, beta):
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
        if np.linalg.norm(u - old_u) < 10e-13:
            break
        old_u = u
    return u, (l - beta) / alpha


def qr_algoritm(A):
    rez = np.linalg.eigvals(A)
    print(sorted(rez))

    Q, R = householder_transformation(A)
    print(sorted(abs(R.diagonal())))



def least_squares(A, b_):
    a_t = A.transpose()
    matrix = a_t.dot(A)
    b = a_t.dot(b_)

    if matrix.shape == ():
        return b / matrix

    return gauus(matrix, b)


def householder_transformation_solver(A, b_):
    b, R = householder_transformation(A,b_)

    answer = reversal_gauus(R,b)
    return  answer


def householder_transformation(A,b_ = None):
    n = len(A)

    Q = np.identity(n)
    R = np.copy(A)
    b = np.zeros(n)

    if b_ is not None:
        b = b_.copy()

    for i in range(n - 1):
        a = R[i:, i]

        a_ = np.zeros_like(a)
        a_[0] = math.copysign(np.linalg.norm(a), -A[i, i])
        u = a + a_
        v = u / np.linalg.norm(u)

        Q_i = np.identity(n)
        Q_i[i:, i:] -= 2.0 * np.outer(v, v)

        R = np.dot(Q_i, R)
        Q = np.dot(Q, Q_i.transpose())
        if b_ is not None:
            b = Q_i.dot(b)

    if b_ is not None:
        return (b, R)
    else :
        return (Q, R)


def gmres(A,b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(matrix)
    tmp = b.copy()
    x = np.zeros(n)
    x1 = np.zeros(n)
    K = np.copy(np.hstack(b[:, None]))
    while True:
        t = A.dot(K)
        rez = least_squares(t,b)
        x = K.dot(rez)
        if np.linalg.norm(x - x1) < 10e-7:
            return x
        tmp = A.dot(tmp)
        x1 = x.copy()
        K = np.c_[K, tmp]

def test_all(n, size, number_of_repeats, isEasy):
    sizeB = 10
    conditionsA = []
    conditionsA_ = []
    conditionsB = []

    inverse_timesA = []
    inverse_timesA_ = []
    inverse_timesB = []

    gauus_times = []
    gauus_norm = []

    lu_decomposition_times = []
    lu_solve_times = []
    lu_norm = []

    cholesky_decomposition_times = []
    cholesky_norm = []

    sor_times = []
    sor_norm = []

    reflection_times = []
    reflection_norm = []

    least_squares_morm = []
    least_squares_times = []

    gmres_norm = []
    gmres_times = []

    lambda_norm = []
    stepen_tiems = []

    qr_times = []

    danilevsky_times = []

    for i in range(number_of_repeats):
        print("________________" + str(i + 1) + " iteration________________")

        matrixA, y, b = generate_matrix(size=size, n=n, simple_random=isEasy)
        matrixB = matrixA[:sizeB, :sizeB]
        matrixA_ = matrixA[:, :20 * n]

        start_time = time.time()
        conditionsA.append(condition_number(matrixA))
        inverse_timesA.append(time.time() - start_time)
        print("Condition of matrix A", conditionsA[-1])

        start_time = time.time()
        conditionsB.append(condition_number(matrixB))
        inverse_timesB.append(time.time() - start_time)
        print("Condition of matrix B", conditionsB[-1])

        start_time = time.time()
        conditionsA_.append(condition_number(matrixA_))
        inverse_timesA_.append(time.time() - start_time)
        print("Condition of matrix A_", conditionsA_[-1])

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
        rez = method_square_root(matrixA, b)
        cholesky_decomposition_times.append(time.time() - start_time)
        cholesky_norm.append(max_norm_of_vectors(rez, y))
        print("Cholesky answer", np.allclose(rez, y))

        start_time = time.time()
        rez = sor(matrixA, b, (n + 1) / 6)
        sor_times.append(time.time() - start_time)
        sor_norm.append(max_norm_of_vectors(rez, y))
        print("SOR answer", np.allclose(rez, y))

        start_time = time.time()
        rez = householder_transformation_solver(matrixA, b)
        reflection_times.append(time.time() - start_time)
        reflection_norm.append(max_norm_of_vectors(rez, y))
        print("householder_transformation_solver answer", np.allclose(rez, y))

        start_time = time.time()
        rez = least_squares(matrixA, b)
        least_squares_times.append(time.time() - start_time)
        least_squares_morm.append(np.linalg.norm(matrixA.dot(rez) - b))

        start_time = time.time()
        rez = gmres(matrixA, b)
        gmres_times.append(time.time() - start_time)
        gmres_norm.append(max_norm_of_vectors(rez, y))


        start_time = time.time()
        u1, l1 = find_lambda_with_vector(matrixB, 1, 0)
        stepen_tiems.append(time.time() - start_time)
        lambda_norm.append(max_norm_of_vectors(matrixB.dot(u1) , l1 * u1))

        u2, l2 = find_lambda_with_vector(matrixB, -1, l1)
        lambda_norm.append(max_norm_of_vectors(matrixB.dot(u2), l2 * u2))

        start_time = time.time()
        qr_algoritm(matrixB)
        qr_times.append(time.time() - start_time)

        start_time = time.time()
        danilevsky_method(matrixB)
        danilevsky_times.append(time.time() - start_time)



    print("Average conditional of matrix A number: ", sum(conditionsA) / number_of_repeats, file=f)
    print("Max and min conditional of matrix A number: ", max(conditionsA), min(conditionsA), file=f)
    print("Average search time for inverse matrix A in sec: ", sum(inverse_timesA) / number_of_repeats, file=f)
    print(file=f)

    print("Average conditional of matrix B number: ", sum(conditionsB) / number_of_repeats, file=f)
    print("Max and min conditional of matrix B number: ", max(conditionsB), min(conditionsB), file=f)
    print("Average search time for inverse matrix B in sec: ", sum(inverse_timesB) / number_of_repeats, file=f)
    print(file=f)

    print("Average conditional of matrix A_ number: ", sum(conditionsA_) / number_of_repeats, file=f)
    print("Max and min conditional of matrix A_ number: ", max(conditionsA_), min(conditionsA_), file=f)
    print("Average search time for inverse matrix A_ in sec: ", sum(inverse_timesA_) / number_of_repeats, file=f)
    print(file=f)
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

    print("Average time for solving square root in sec: ",
          sum(cholesky_decomposition_times) / number_of_repeats,
          file=f)
    print("Average square root norm: ", sum(cholesky_norm) / number_of_repeats, file=f)
    print("Max and min square root norm: ", max(cholesky_norm), min(cholesky_norm), file=f)
    print(file=f)

    print("Average time of SOR in sec: ", sum(sor_times) / number_of_repeats, file=f)
    print("Average SOR norm: ", sum(sor_norm) / number_of_repeats, file=f)
    print("Max and min SOR norm: ", max(sor_norm), min(sor_norm), file=f)
    print(file=f)

    print("Average time of reflection solving in sec: ", sum(reflection_times) / number_of_repeats, file=f)
    print("Average least reflection solving norm: ", sum(reflection_norm) / number_of_repeats, file=f)
    print("Max and min least reflection solving norm: ", max(reflection_norm), min(reflection_norm), file=f)
    print(file=f)

    print("Average time of least squares in sec: ", sum(least_squares_times) / number_of_repeats, file=f)
    print("Average least squares norm: ", sum(least_squares_morm) / number_of_repeats, file=f)
    print("Max and min least squares norm: ", max(least_squares_morm), min(least_squares_morm), file=f)
    print(file=f)

    print("Average time of qmres in sec: ", sum(gmres_times) / number_of_repeats, file=f)
    print("Average least qmres norm: ", sum(gmres_norm) / number_of_repeats, file=f)
    print("Max and min qmres norm: ", max(gmres_norm), min(gmres_norm), file=f)
    print(file=f)

    print("Average time of stepen method in sec: ", sum(stepen_tiems) / number_of_repeats, file=f)
    print("Average eigvals norm of step: ", sum(lambda_norm) / len(lambda_norm), file=f)
    print("Max and min norm eigvals of step: ", max(lambda_norm), min(lambda_norm), file=f)
    print(file=f)

    print("Average time QR algoritm in sec: ", sum(qr_times) / number_of_repeats, file=f)
    print(file=f)

    print("Average time danilevsky with solving polynom in sec: ", sum(danilevsky_times) / number_of_repeats, file=f)
    print(file=f)


def main(f, isEasy, number_of_repeats):
    precision = 5 if isEasy else 13
    size = 3 if isEasy else 256
    n = 7

    np.set_printoptions(precision=precision)
    test_all(n, size, number_of_repeats,isEasy)


if __name__ == '__main__':
    f = open("out.txt", mode="w")
    main(f=f,
         isEasy=False,
         number_of_repeats=100)
