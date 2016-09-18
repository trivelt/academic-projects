#!/usr/bin/python

line = """napisz wielowierszowy
to jest kolejny wiersz
a to jeszcze jeden
Tu zas mamy ostatnia linijke"""

line = line.replace("\n", " ")
l = line.split( " ")

suma = sum(len(x) for x in l)

print "Laczna dlugosc wyrazow w napisie to", suma