import numpy as np
from numpy import random as rand
import random
"""
for row in xrange(pivot_row+1, n):
            multiplier = A[row][pivot_row]/A[pivot_row][pivot_row]
            #the only one in this column since the rest are zero
            A[row][pivot_row] = multiplier
            for col in xrange(pivot_row + 1, n):
                A[row][col] = A[row][col] - multiplier*A[pivot_row][col]
            #Equation solution column
            b[row] = b[row] - multiplier*b[pivot_row]
"""


def swap_cols(matrix, first, second):
    matrix[:, [first, second]] = matrix[:, [second, first]]


def print_matrix(matrix):
    print("---------------------------------------")
    for line in matrix:
        print(line)
    print("---------------------------------------")


def solve_from(A, b):
    n = len(A)
    x = np.zeros(n)
    k = n - 1
    x[k] = b[k] / A[k, k]
    while k >= 0:
        x[k] = (b[k] - np.dot(A[k, k + 1:], x[k + 1:])) / A[k, k]
        k -= 1
    return x

def gauus_by_row(A, b):
    n = len(A)
    for col in range(n - 1):
        max = 0
        max_col = 0
        for row in range(col, n):
            if abs(A[col][row]) > max:
                max = abs(A[col][row])
                max_col = col
        swap_cols(A, col, max_col)
        for row in range(col+1, n):
            multiplier = A[row][col] / A[col][col]
            A[row][col] = 0
            for next_col in range(col+1, n):
                A[row][next_col] = A[row][next_col] - multiplier*A[col][next_col]
            b[row] = b[row] - multiplier*b[col]

    return solve_from(A, b)



def mkk(A, b):
    n = len(A)
    for col in range(n - 1):
        for row in range(col + 1, n):
            multiplier = A[row][col] / A[col][col]
            A[row][col] = 0
            for next_col in range(col + 1, n):
                if row+1 != next_col:
                    A[row][next_col] = A[next_col][row] = A[row][next_col] - multiplier * A[col][next_col]
                else:
                    A[row][next_col] = A[row][next_col] - multiplier * A[col][next_col]
            b[row] = b[row] - multiplier * b[col]
        print_matrix(A)
    return solve_from(A, b)


def main():
    size = 4
    n = 7
    np.set_printoptions(precision=2)
    matrixA = np.zeros((size, size))
    y = np.zeros(size)
    for i in range(0, size):
        y[i] = ((2**n)*2) * rand.random_sample() - (2**n) #  random.randrange(-10, 10)
        for j in range(i+1, size):
            matrixA[i][j] = matrixA[j][i] = ((2**n)*2) * rand.random_sample() - (2**n) #random.randrange(-10, 10)

    row, col = np.diag_indices_from(matrixA)
    matrixA[row, col] = np.absolute(matrixA).sum(axis=1)

    print_matrix(matrixA)
    print("-------------yyyyyyyyyy----------------------")
    print(y)

    b = matrixA.dot(y)
    print("------------bbbbbbbbbbb---------------------")
    print(b)
    print("---------------------------------------")
    rez = gauus_by_row(matrixA.copy(), b.copy())
    print("Rez:", rez, np.allclose(rez, y))
    rez = mkk(matrixA.copy(), b.copy())
    print("Rez:", rez, np.allclose(rez, y))


if __name__ == '__main__':
    main()