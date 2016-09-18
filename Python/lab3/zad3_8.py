#!/usr/bin/python

alist = [12, 30, 182, 182, 2, 9, 19]
blist = [7, 19, 10, 88, 2, 4, 19]

aset = set(alist)
bset = set(blist)

clist = list(aset.intersection(bset))
print "Czesc wspolna to", clist

dlist = list(aset.union(bset))
print "Suma zbiorow to", dlist