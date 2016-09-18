#!/usr/bin/python

line = """napisz wielowierszowy
to jest kolejny wiersz
a to jeszcze jeden
Tu zas mamy ostatnia linijke"""

line = line.replace("\n", " ")
l = line.split( " ")

firstLetters = ""
lastLetters = ""
for x in l:
    firstLetters += x[0]
    lastLetters += x[len(x)-1]
print "Napis zlozony z pierwszych liter wyrazow: ", firstLetters
print "Napis zlozony z ostatnich liter wyrazow: " , lastLetters