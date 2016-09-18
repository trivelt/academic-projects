#!/usr/bin/python
from copy import deepcopy
from sys import stdout
printf = stdout.write

def check(a, b):
    length = len(a[0])
    isOk = True
    for i in range(length):
        for j in range(length):
            if abs(a[i][j] - b[j][j]) > 10e-5:
                print("roznica = " + str(abs(a[i][j] - b[i][j])))
                return false
    return True
    
def multiply(A, B):
    mA = len(A)
    nA = len(A[0])
    mB = len(B)
    nB = len(B[0])
    if nA != mB:
        raise "Illegal matrix dimension"
    C = list()
    for i in range(mA):
        C.append([0 for i in range(nB)])
        for j in range(nB):
            for k in range(nA):
                C[i][j] += A[i][k] * B[k][j]
    return C                

def showMatrix(a):
    for i in range(len(a[0])):
        for j in range(len(a[0])):
            printf(str(a[i][j]) + " ")
        print("")

		
if __name__ == "__main__":
    matrix1 = [[0.64, 0.32, 0.04], [0.4, 0.5, 0.1], [0.25, 0.5, 0.25]]
    matrix2 = [[0.3, 0.6, 0.1], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]]

    matrixTmp = deepcopy(matrix2)
    matrix2 = multiply(matrix2, matrix1)

    while(not check(matrix2, matrixTmp)):
        matrixTmp = deepcopy(matrix2)
        matrix2 = multiply(matrix2, matrix1)
	    
    showMatrix(matrix2)	    
