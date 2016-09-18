#!/usr/bin/python
from sys import exit

line = """napisz wielowierszowy
to jest kolejny wiersz
a to jeszcze jeden
Tu zas mamy ostatnia linijke"""

line = line.replace("\n", " ")
l = line.split(" ")
print "Napis zawiera ", len(l), " wyrazow"