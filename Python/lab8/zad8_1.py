#!/usr/bin/python

def solve1(a, b, c):
    x = 0.0
    if a == 0:
	if c == 0:
	    print "Rownanie nieoznaczone"
	else:
	    print "Brak rozwiazan"
    else:
	print "x = " + str(-c/a)

solve1(4,2,3)
