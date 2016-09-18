#!/usr/bin/python

"""
Czasy mierzone systemowym poleceniem "time":
Dla i=16, j=9:
	*wersja rekurencyjna: 1.355 s.
	*wersja dynamiczna: 0.28 s.

Dla i=16, j=10:
	*wersja rekurencyjna: 3.506 s.
	*wersja dynamiczna: 0.33 s.

Dla i=16, j=13:
	*wersja rekurencyjna: 44.596 s.
	*wersja dynamiczna: 0.32 s.
"""

def p_rek(i, j):
    if i == 0 and j == 0:
	return 0.5
    elif i == 0 and j != 0:
	return 1.0
    elif i != 0 and j == 0:
	return 0.0
    else:
	return 0.5*( p_rek(i-1, j) + p_rek(i, j-1) )

def p_dyn(i, j):
    tab = [ [0]*(j+1) for x in range(i+1)]
    for x in range(i+1):
	for y in range(j+1):
	    if x == 0 and y == 0:
		tab[x][y] = 0
	    elif x == 0 and y != 0:
		tab[x][y] = 1.0
	    elif x != 0 and y == 0:
		tab[x][y] = 0.0
	    else:
		tab[x][y] = 0.5*(tab[x-1][y] + tab[x][y-1])
    return tab[i][j]


#print p_rek(16, 13)
print p_dyn(16, 13)

