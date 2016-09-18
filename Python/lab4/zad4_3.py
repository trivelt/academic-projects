#!/usr/bin/python

def factorial(n):
    result = n
    while n:
	n -= 1
	if n == 0:
	    return result
	result *= n

print factorial(5)
