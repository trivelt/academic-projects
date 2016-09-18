#!/usr/bin/python

def zad3_6(rows, columns):
	horizontalLine = "+---"
	verticalLine = "|   "

	print columns*horizontalLine+"+"

	while rows:
	    print columns*verticalLine+"|"
	    print columns*horizontalLine+"+"
	    rows -= 1


def zad3_5(length):
	line = "|...."

	print (length-1)*line+"|"
	numbers = range(length)
	if length >= 12:
	    numberPocz = numbers[:11]
	    numberKonc = numbers[11:]
	    list1 =  "    ".join(["%s" %el for el in numberPocz])
	    list2 = "   ".join(["%s" %el for el in numberKonc])
	    print list1+"   "+list2

	else:
	    print "    ".join(["%s" %el for el in numbers])

zad3_6(3,4)
print "\n\n"
zad3_5(13)
