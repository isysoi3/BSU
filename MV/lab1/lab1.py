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


def gauus(A, b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(matrix)
    for col in range(n - 1):
        for row in range(col + 1, n):
            multiplier = matrix[row][col] / matrix[col][col]
            matrix[row][col] = 0
            for next_col in range(col + 1, n):
                matrix[row][next_col] = matrix[row][next_col] - multiplier * matrix[col][next_col]
            b[row] = b[row] - multiplier * b[col]

    return solve(matrix, b)


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


def cholesky_decomposition(A, b_):
    matrix = A.copy()
    b = b_.copy()
    n = len(A)

    R = np.zeros((n, n))
    D = np.zeros((n, n))
    for i in range(0, n):
        for j in range(i, n):
            if i < j:
                R[i][j] = (1/(D[i][i] * R[i][i])) * (matrix[i][j] - sum([D[k][k] * R[k][i] * R[k][j] for k in range(i)]))
            elif i == j:
                w = matrix[i][i] - sum([ D[k][k] * (R[k][i] ** 2) for k in range(i)])
                D[i][i] = np.sign(w)
                R[i][i] = np.sqrt(w)

    return solve_cholesky(R, b)


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
    return matrix, y


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


def solve_cholesky(upper_triangular, b_):
    L = upper_triangular.transpose().copy()
    U = upper_triangular.copy()
    b = b_.copy()
    return solve(U, gauus(L, b))


def solve_lu(lower_triangular, upper_triangular, b_):
    L = lower_triangular.copy()
    U = upper_triangular.copy()
    b = b_.copy()
    n = len(L)
    y = np.zeros(n)

    for i in range(n):
        y[i] = b[i] - sum([L[i][g] * y[g] for g in range(i-1, -1 , -1)])

    return solve(U, y)


def sor(A, b_, parameter=1.25, x0=None, eps=1e-13, max_iteration=100):
    """
    Parameters
    ----------
    matrix  : list of list of floats : coefficient matrix
    parameter  : float : weight
    x0 : list of floats : initial guess
    eps: float : error tolerance
    max_iteration: int

    Returns
    -------
    list of floats
        solution to the system of linear equation

    Raises
    ------
    ValueError
        Solution does not converge
    """
    n = len(A)
    matrix = A.copy()
    b = b_.copy()
    x0 = [0] * n if x0 is None else x0
    x1 = x0[:]

    for __ in range(max_iteration):
        for i in range(n):
            s = sum(-matrix[i][j] * x0[j] for j in range(n) if i != j)
            x0[i] = parameter * (b[i] + s) / matrix[i][i] + (1 - parameter) * x0[i]
        if all(abs(x0[i] - x0[i]) < eps for i in range(n)):
            return x0
        x0 = x0[:]
    raise ValueError('Solution does not converge')


def main():
    size = 3
    n = 7
    precision = 2

    np.set_printoptions(precision=precision)
    matrixA, y = generate_matrix(size=size, n=n,simple_random=True)
    determinant = np.linalg.det(matrixA)

    if determinant == 0:
        print("Invertible matrix")
        return None

    b = matrixA.dot(y)
    print("Condition of matrix ", condition_number(matrixA))

    print_matrix(matrixA)
    print("-------------yyyyyyyyyy----------------------")
    print(y)
    print("------------bbbbbbbbbbb---------------------")
    print(b)
    print("---------------------------------------")
    rez = gauus_by_row(matrixA, b)
    print("Gauus by row answer:", rez, "\nIs equal to y", np.allclose(rez, y))
    L, U = lu_decomposition(matrixA)
    rez = solve_lu(L, U, b)
    print("LU answer:", rez, "\nIs equal to y", np.allclose(rez, y))

    rez = cholesky_decomposition(matrixA, b)
    print("Cholesky answer:", rez, "\nIs equal to y", np.allclose(rez, y))

    rez = sor(A=matrixA, b_=b, parameter=(n + 1) / 6)
    print("SOR answer:", rez, "\nIs equal to y", np.allclose(rez, y))


if __name__ == '__main__':
    main()
