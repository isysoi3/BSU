import numpy as np
from numpy import random as rand
import random


def swap_cols(matrix, first, second):
    matrix[:, [first, second]] = matrix[:, [second, first]]


def print_matrix(matrix):
    print("---------------------------------------")
    for line in matrix:
        print(line)
    print("---------------------------------------")


def solve(A, b):
    n = len(A)
    x = np.zeros(n)
    k = n - 1
    x[k] = b[k] / A[k, k]
    while k >= 0:
        x[k] = (b[k] - np.dot(A[k, k + 1:], x[k + 1:])) / A[k, k]
        k -= 1
    return x


def gauus_by_row(A, b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(matrix)
    for col in range(n - 1):
        max = 0
        max_col = 0
        for row in range(col, n):
            if abs(matrix[col][row]) > max:
                max = abs(matrix[col][row])
                max_col = col
        swap_cols(matrix, col, max_col)
        for row in range(col + 1, n):
            multiplier = matrix[row][col] / matrix[col][col]
            matrix[row][col] = 0
            for next_col in range(col + 1, n):
                matrix[row][next_col] = matrix[row][next_col] - multiplier * matrix[col][next_col]
            b[row] = b[row] - multiplier * b[col]

    return solve(matrix, b)


def mkk(A, b):
    # TODO: дописать
    n = len(A)
    for col in range(n - 1):
        for row in range(col + 1, n):
            multiplier = A[row][col] / A[col][col]
            A[row][col] = 0
            for next_col in range(col + 1, n):
                if row + 1 != next_col:
                    A[row][next_col] = A[next_col][row] = A[row][next_col] - multiplier * A[col][next_col]
                else:
                    A[row][next_col] = A[row][next_col] - multiplier * A[col][next_col]
            b[row] = b[row] - multiplier * b[col]
        print_matrix(A)
    return solve(A, b)


def inverse_matrix(A):
    matrix = A.copy()
    n = len(matrix)
    identity_matrix = np.identity(n)

    for row in range(n):
        multiplier = matrix[row][row]
        for i in range(row, n):
            matrix[row][i] /= multiplier
        for i in range(0, n):
            identity_matrix[row][i] /= multiplier
        for next_row in range(row+1, n):
            multiplier = matrix[next_row][row]
            for i in range(row, n):
                matrix[next_row][i] -= multiplier * matrix[row][i]
            for i in range(0, n):
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
    return max(np.sum(np.absolute(matrix), axis=0))


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
    print_matrix(matrix)
    return matrix, y


def pivot_matrix(data):
    data = data.copy()
    rows, row_pos = np.unique(data[:, 0], return_inverse=True)
    cols, col_pos = np.unique(data[:, 1], return_inverse=True)

    pivot_table = np.zeros((len(rows), len(cols)), dtype=data.dtype)
    pivot_table[row_pos, col_pos] = data[:, 2]
    return pivot_table

def lu_decomposition(A):
    matrix = A.copy()
    n = len(matrix)
    identity_matrix = np.identity(n)

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
            U[i][j] =  matrix[i][j]

    for i in range(1,n):
        for j in range(i):
            L[i][j] =  matrix[i][j]

    print_matrix(U)
    print_matrix(L)
    return L, U


def solve_lu(L, U, b):
    b = np.zeros(0)




def main():
    size = 3
    n = 7
    precision = 2

    np.set_printoptions(precision=precision)
    matrixA, y = generate_matrix(size=size, n=n)
    determinant = np.linalg.det(matrixA)

    if determinant == 0:
        print("Invertible matrix")
        return None

    b = matrixA.dot(y)
    print("Condition of matrix ", condition_number(matrixA))
    """
    print_matrix(matrixA)
    print("-------------yyyyyyyyyy----------------------")
    print(y)
    print("------------bbbbbbbbbbb---------------------")
    print(b)
    print("---------------------------------------")
    rez = gauus_by_row(matrixA, b)
    print("Rez:", rez, np.allclose(rez, y))
    """

    L, U = lu_decomposition(matrixA)
    solve_lu(L, U, b)
    """
    rez = mkk(matrixA.copy(), b.copy())
    print("Rez:", rez, np.allclose(rez, y))
    """


if __name__ == '__main__':
    main()
