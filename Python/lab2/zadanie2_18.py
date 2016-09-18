#!/usr/bin/python

liczba = 13934001001304200120
strLiczba = str(liczba)
liczbaZer = 0

for x in strLiczba:
    if x == "0":
	liczbaZer += 1

print "Liczba zawiera", liczbaZer, "zer"