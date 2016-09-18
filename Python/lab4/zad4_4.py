#!/usr/bin/python

def fibonacci(p):
    n = 0
    m = 1
    while p:
	p -= 1
	temp = m
	m = m+n
	n = temp
    return n

print fibonacci(17)
