#!/usr/bin/python
# Maciej Michalec, grupa 2
from sys import argv
from math import sqrt

def get_param_value(param):
    value = param[2:]
    try:
        value_number = float(value)
        return value_number
    except:
        return None

if len(argv) < 4:
    print("Zla liczba argumentow. Podaj 3 wspolczynniki rownania kwadratowego w postaci a=liczba, b=liczba, c=liczba (kolejnosc dowolna)")
    exit(1)
    
a = b = c = None    
for param in argv:
    if param.lower().startswith("a="):
        value = get_param_value(param)
        if value is not None:
            a = value
    elif param.lower().startswith("b="):
        value = get_param_value(param)
        if value is not None:
            b = value        
    elif param.lower().startswith("c="):
        value = get_param_value(param)
        if value is not None:
            c = value        
        
if a==None or b==None or c==None:
    print("Bledne argumenty. Nie znaleziono wszystkich trzech wspolczynnikow")
    exit(1)

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
