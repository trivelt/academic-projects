#!/usr/bin/python

line = """napisz wielowierszowy
to jest kolejny wiersz
a to jeszcze jeden
Tu zas mamy ostatnia linijke"""

line = line.replace("\n", " ")
l = line.split( " ")

alfabetycznie = sorted(l, cmp = lambda x, y: cmp(x.lower(), y.lower()))
dlugosciowo = sorted(l, cmp = lambda x, y: cmp(len(x), len(y)))

print alfabetycznie
print dlugosciowo