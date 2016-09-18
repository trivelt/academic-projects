#!/usr/bin/python

line = """napisz wielowierszowy
to jest kolejny wiersz
a to jeszcze jeden
Tu zas mamy ostatnia linijke"""

line = line.replace("\n", " ")
l = line.split( " ")

dlugoscWyrazow = {(len(x)) : x for x in l}

longest =  dlugoscWyrazow.get(max(dlugoscWyrazow.keys()))
shortest = dlugoscWyrazow.get(min(dlugoscWyrazow.keys()))

print "Najdluzszy wyraz to", longest + ", ktorego liczba znakow to",  len(longest)
print "Najkrtoszy wyraz to", shortest +", ktorego liczba znakow to", len(shortest)