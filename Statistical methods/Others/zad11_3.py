#!/usr/bin/python
from zad11_1 import getRandomNumbersList

def swap(L, left, right):
    """Zamiana miejscami dwoch elementow na liscie."""
    tmp = L[left]
    L[left] = L[right]
    L[right] = tmp

def shakersort(L, left, right, cmpfunc=cmp):
    k = right
    while left < right:
        for j in range(right, left, -1): # od prawej
            if cmpfunc(L[j-1], L[j]) > 0:
                swap(L, j-1, j)
                k = j
        left = k
        for j in range(left, right):  # od lewej
            if cmpfunc(L[j], L[j+1]) > 0:
                swap(L, j, j+1)
                k = j
        right = k

def myCmpFunc(p, q):
	if p > q:
		return -1
	elif p < q:
		return 1
	else:
		return 0

L = getRandomNumbersList(20)
print L # losowo
shakersort(L, 0, 19)
print L # rosnaco
shakersort(L, 0, 19, myCmpFunc)
print L # malejaco
shakersort(L, 10, 19, cmpfunc=lambda x,y: -myCmpFunc(x,y)) 
print L # polowa malejaco, polowa rosnaco
