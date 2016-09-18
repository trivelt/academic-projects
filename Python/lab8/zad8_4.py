#!/usr/bin/python
from math import sqrt

def heron(a, b, c):
    if a>=b+c or b>=a+c or c>=a+b:
	raise ValueError("Nieprawidlowe argumenty")
    p = (a+b+c)/2.0
    S = sqrt(p*(p-a)*(p-b)*(p-c))
    return S

print "Pole trojkata to " + str(heron(3, 4, 5))