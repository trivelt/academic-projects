#!/usr/bin/python

from random import randint, choice, gauss
from math import sqrt

def getRandomNumbersList(N):
    L = [x for x in range(N)]
    R = list()
    for i in range(N):
	rNum = choice(L)
	R.append(rNum)
	L.remove(rNum)
    return R
    
def getAlmostSortedNumbersList(N):
    L = [x for x in range(N)]
    if len(L) < 2:
	return L
    for i in range(randint(4,8)):
	rIndex = randint(0,N-1)
	if rIndex != 0:
	    tmp = L[rIndex]
	    L[rIndex] = L[rIndex-1]
	    L[rIndex-1] = tmp
	else:
	    tmp = L[0]
	    L[0] = L[1]
	    L[1] = tmp
    return L

def getReversedAlmostSortedNumbersList(N):
    L = getAlmostSortedNumbersList(N)
    L.reverse()
    return L

def getGaussianRandomNumbersList(N):
    L = list()
    for i in range(N):
	rNumber = round(gauss(100,30))
	L.append(int(rNumber))
    return L

def getRepeatedRandomNumbersList(N, sqRoot=False):
    L = list()
    if sqRoot is True:
        k = int(round(sqrt(N)))
    else:
        k = int(round(N/2))
    for i in range(N):
	rNumber = randint(0,k)
	L.append(rNumber)
    return L

if __name__ == "__main__":
    LL = getRandomNumbersList(15)
    print LL

    RR = getAlmostSortedNumbersList(15)
    print RR

    RL = getReversedAlmostSortedNumbersList(15)
    print RL

    GL = getGaussianRandomNumbersList(15)
    print GL

    RN = getRepeatedRandomNumbersList(15)
    print RN