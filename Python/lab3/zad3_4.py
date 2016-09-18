#!/usr/bin/python
import re

while(True):
    inp = raw_input(">>")
    if inp == "stop":
	break
    if re.findall(r"\D", inp):
	print "Nalezy podawac liczby, nie tekst!"
	continue
    x = int(inp)
    print x, pow(x,3)
