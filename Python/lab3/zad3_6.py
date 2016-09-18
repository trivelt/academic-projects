#!/usr/bin/python

horizontalLine = "+---"
verticalLine = "|   "

rows = 2
columns  = 4

print columns*horizontalLine+"+"

while rows:
    print columns*verticalLine+"|"
    print columns*horizontalLine+"+"
    rows -= 1