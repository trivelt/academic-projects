#!/usr/bin/python

L = [1, 91, 501, 88, 18, 7, 345, 13]
L2 = map(str, L)
napis = ""

for x in L2:
    napis += x.zfill(3) + " "

print napis