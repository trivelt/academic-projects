#!/usr/bin/python
from random import seed, random

def calc_pi(n=100):
    """Obliczanie liczby pi metoda Monte Carlo
       n oznacza liczbe losowanych punktow."""
    seed()
    nk = 0
    m = n
    while n:
        x = random()
        y = random()
	if x*x+y*y <= 1:
	    nk += 1
	n -= 1
    print "Liczba punktow w kwadracie wynosi " + str(m)
    print "Liczba punktow w kole wynosi " + str(nk)
    s = 4.0 * nk/m
    print "Liczba PI wynosi " + str(s)

calc_pi(10000000)