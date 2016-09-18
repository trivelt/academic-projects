#!/usr/bin/python

def factorial(n):
    result = n
    while n:
	n -= 1
	if n == 0:
	    return result
	result *= n


def fibonacci(p):
    n = 0
    m = 1
    while p:
	p -= 1
	temp = m
	m = m+n
	n = temp
    return n

