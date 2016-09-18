#!/usr/bin/python
# Maciej Michalec, grupa 2
from sys import argv
from math import sqrt

if len(argv) < 4:
    print("Zla liczba argumentow. Podaj 3 liczby, ktore sa wspolczynnikami rownania kwadratowego Ax**2 + Bx + C")
    exit(1)
    
wspolczynniki = []
for param in argv[1:4]:
    try:
        number = float(param)
        wspolczynniki.append(number)
    except:
        print("Argument " + str(param) + " nie jest poprawna liczba zmiennoprzecinkowa")
        exit(1)

a, b, c = wspolczynniki    
delta = b**2 - 4*a*c
#print("Delta: " + str(delta))
if delta > 0:
    sqrt_delta = sqrt(delta)
else:
    sqrt_delta = sqrt(-delta)
    
if a == 0:
    if b == 0:
        print("Rownanie sprzeczne")
    else:
        print("Pierwiastek rownania (liniowego): " + str(-c / b))
    exit(0)

if delta > 0:
    print("Pierwiastki: ")
    print( "1) " + str((-b + sqrt_delta) / 2*a ))
    print( "2) " + str((-b - sqrt_delta) / 2*a ))
elif delta == 0:
    print("Pierwiastek: ")
    print( "1) " + str(-b / 2*a ))
elif delta < 0:
    print("Pierwiastki:")
    print( "1) " + str(-b / 2*a) + " + i*" + str(sqrt_delta / 2*a))
    print( "1) " + str(-b / 2*a) + " - i*" + str(sqrt_delta / 2*a))
    
exit(0)
