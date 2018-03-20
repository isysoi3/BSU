import numpy as np
from numpy import random as rand
import random
import time


def swap_cols(matrix, first, second):
    matrix[:, [first, second]] = matrix[:, [second, first]]


def print_matrix(matrix):
    print("---------------------------------------")
    for line in matrix:
        print(line)
    print("---------------------------------------")


def reversal_gauus(A, b):
    n = len(A)
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        tmp_x = b[i]
        for g in range(i + 1, n):
            tmp_x -= A[i][g] * x[g]
        x[i] = tmp_x / A[i][i]

    return x


def gauus(A, b_, is_for_L=False):
    matrix = A.copy()
    b = b_.copy()
    n = len(matrix)
    for col in range(n):
        for row in range(col + 1, n):
            multiplier = matrix[row][col] / matrix[col][col]
            for column in range(col, n):
                matrix[row][column] -= multiplier * matrix[col][column]
            b[row] -= multiplier * b[col]

    return reversal_gauus(matrix, b) if not is_for_L else [b[i] / matrix[i][i] for i in range(n)]


def gauus_by_row(A, b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(matrix)

    for col in range(0, n):
        max = 0
        max_col = 0
        for row in range(col, n):
            if abs(matrix[col][row]) > max:
                max = abs(matrix[col][row])
                max_col = col
        swap_cols(matrix, col, max_col)
        for row in range(col + 1, n):
            multiplier = matrix[row][col] / matrix[col][col]
            for column in range(col, n):
                matrix[row][column] -= multiplier * matrix[col][column]
            b[row] -= multiplier * b[col]
    return reversal_gauus(matrix, b)


def cholesky_decomposition(A, b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(A)
    R = np.zeros((n, n))
    D = np.zeros((n, n))

    for i in range(0, n):
        for j in range(i, n):
            if i < j:
                R[i][j] = (1 / (D[i][i] * R[i][i])) * (matrix[i][j] - sum([D[k][k] * R[k][i] * R[k][j] for k in range(i)]))
            elif i == j:
                w = matrix[i][i] - sum([D[k][k] * (R[k][i] ** 2) for k in range(i)])
                D[i][i] = np.sign(w)
                R[i][i] = np.sqrt(w)

    return solve_cholesky(R, b)


def solve_cholesky(upper_triangular, b_):
    L = upper_triangular.transpose().copy()
    U = upper_triangular.copy()
    b = b_.copy()
    return reversal_gauus(U, gauus(L, b, is_for_L=True))


def inverse_matrix(A):
    matrix = A.copy()
    n = len(matrix)
    identity_matrix = np.identity(n)

    for row in range(n):
        multiplier = matrix[row][row]
        for i in range(0, n):
            identity_matrix[row][i] /= multiplier
            matrix[row][i] /= multiplier
        for next_row in range(row+1, n):
            multiplier = matrix[next_row][row]
            for i in range(row, n):
                matrix[next_row][i] -= multiplier * matrix[row][i]
                identity_matrix[next_row][i] -= multiplier * identity_matrix[row][i]
            for i in range(0, row):
                identity_matrix[next_row][i] -= multiplier * identity_matrix[row][i]

    for row in range(n - 1, -1, -1):
        for next_row in range(row - 1,  -1, -1):
            multiplier = matrix[next_row][row]
            for i in range(row, -1):
                matrix[next_row][i] -= multiplier * matrix[row][i]
            for i in range(0, n):
                identity_matrix[next_row][i] -= multiplier * identity_matrix[row][i]

    return identity_matrix


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
            matrix[i][j] = matrix[j][i] = random.randrange(-10, 10) if simple_random else ((2 ** n) * 2) * rand.random_sample() - (2 ** n)

    row, col = np.diag_indices_from(matrix)
    matrix[row, col] = np.absolute(matrix).sum(axis=1)
    return matrix, y, matrix.dot(y)


def lu_decomposition(A):
    matrix = A.copy()
    n = len(matrix)

    for row in range(n-1):
        for next_row in range(row+1, n):
            multiplier = matrix[next_row][row] / matrix[row][row]
            for i in range(row, n):
                matrix[next_row][i] -= multiplier * matrix[row][i]
            matrix[next_row][row] = multiplier

    U = np.zeros((n,n))
    L = np.identity(n)
    for i in range(n):
        for j in range(i,n):
            U[i][j] = matrix[i][j]

    for i in range(1,n):
        for j in range(i):
            L[i][j] = matrix[i][j]

    return L, U


def solve_lu(lower_triangular, upper_triangular, b_):
    L = lower_triangular.copy()
    U = upper_triangular.copy()
    b = b_.copy()
    n = len(L)
    y = np.zeros(n)

    for i in range(n):
        y[i] = b[i] - sum([L[i][g] * y[g] for g in range(i-1, -1 , -1)])

    return reversal_gauus(U, y)


def sor(A, b_, w, eps=10e-5, max_iteration=1000):
    n = len(A)
    matrix = A.copy()
    b = b_.copy()
    x = np.zeros(n)

    for _ in range(max_iteration):
        for i in range(n):
            x[i] = (1 - w) * x[i] + \
                    w / matrix[i][i] * (b[i]
                        - sum([matrix[i][j] * x[j] for j in range(i)])
                        - sum([matrix[i][j] * x[j] for j in range(i + 1, n)]))
        if np.linalg.norm(np.dot(A, x) - b) < eps:
            return x


def max_norm_of_vectors(vector, y):
    return max([vector[i] - y[i] for i in range(len(y))])


def main(f, isEasy, number_of_repeats):
    precision = 2 if isEasy else 13
    size = 5 if isEasy else 256
    n = 7

    np.set_printoptions(precision=precision)
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
    sor_norm =[]
    for i in range(number_of_repeats):
        print("________________"+ str(i+1) + " iteration________________")

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


    print("Average conditional number: ", sum(conditions)/number_of_repeats, file=f)
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

    print("Average time for solving cholesky decomposition in sec: ", sum(cholesky_decomposition_times) / number_of_repeats,
          file=f)
    print("Average cholesky norm: ", sum(cholesky_norm) / number_of_repeats, file=f)
    print("Max and min cholesky norm: ", max(cholesky_norm), min(cholesky_norm), file=f)
    print(file=f)

    print("Average time of SOR in sec: ", sum(sor_times) / number_of_repeats, file=f)
    print("Average SOR norm: ", sum(sor_norm) / number_of_repeats, file=f)
    print("Max and min SOR norm: ", max(sor_norm), min(sor_norm), file=f)


if __name__ == '__main__':
    f = open("out.txt",mode="w")
    main(f=f,isEasy=False,number_of_repeats=100)
