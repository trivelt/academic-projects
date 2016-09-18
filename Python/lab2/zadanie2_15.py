#!/usr/bin/python

L = [4, 1, 491, 788, 8, 19, 24, 7, 1000]

"""
Polecenie zadania jest dla mnie troche niejasne. 
Rozumiem je w ten sposob, ze nalezy najpierw uszeregowac
w jakiejs kolejnosci (dajmy na to: rosnacej) znajdujace sie 
na liscie liczby, a nastepnie stworzyc, skladajacy sie z ich cyfr
(czyli de facto po prostu liczb)
"""

L.sort()
S = "".join(str(x) for x in L)
print S