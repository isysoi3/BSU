import numpy as np
import sympy as sp
import random


sp.init_printing()
A = [[0.8, 0.2, 0.3], [-0.2, 0.5, -0.3], [-0.4, -0.2, 1.3]]
F = [-1, 4, 5]
B = np.eye(3)-A

# функция возвращает следующий этап
def move(currentI, P):
    temp = random.random()
    i = 0
    k = 0
    while(i < temp):
        i += P[currentI, k]
        k += 1
    return k-1

#Возвращает кси
def ksi(l, A, F, H, Pi, P):
    temp = random.random()
    i=0
    k=0
    while(i < temp):
        i += Pi[k]
        k += 1
    current = k-1
    if( H[current]==0 ):
        return 0
    Q = H[current]/Pi[current]
    ksi = Q*F[current]
    for i in range(l):  
        temp = move(current,P)
        Q *= A[current][temp]/P[current][temp]
        ksi += Q*F[temp]
        current = temp
    return ksi

def solve(n, m, A, F):
    dim = len(A)
    P=np.array([[1/dim for i in range(dim)]for j in range(dim)])#матрица вероятностей прехода
    Pi=np.array([1/dim for i in range(dim)])#вероятности начальных состояний 
    X=[0]*dim
    H=[0]*dim
    for j in range(dim):        
        H[j]=1
        H[j-1]=0
        for i in range(n):
            X[j]+=ksi(m,A,F,H,Pi,P)  
        X[j]/=n    
    return X


def main():
    print(np.linalg.solve(A, F))
    print(solve(1000, 1000, B, F))



if __name__ == '__main__':
    main()
