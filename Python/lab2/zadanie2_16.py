#!/usr/bin/python

line = """Jakis dlugi napis
zawiera ciag znakow GvR ale 
wiecej niz jeden raz
test test GvR test"""

line = line.replace("GvR", "Guido van Rossum")
print line

