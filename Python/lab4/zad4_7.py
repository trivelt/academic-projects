#!/usr/bin/python

def flatten(sequence):
    L = []
    for el in sequence:
	if isinstance(el, (list, tuple)):
	    L += flatten(el)
	else:
	    L.append(el)
    return L


seq = [1,(2,3),[],[4,(5,6,7)],8,[9]]
print flatten(seq)