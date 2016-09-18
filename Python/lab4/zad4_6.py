#!/usr/bin/python

def sum_seq(sequence):
    suma = 0
    for el in sequence:
	if isinstance(el, (list, tuple)):
	    suma += sum_seq(el)
	else:
	    suma += el
    return suma

listka = [19, 10]
krotka = (9, 9, 88)
lista = [1, 2, 3, 4, listka, 6, 7, 8, 9, 10, krotka, 12]

print sum_seq(lista)