#!/usr/bin/python

class Time:
	def __init__(self, seconds=0):
		self.s = seconds
	def __str__(self):
		return "%s sec" % self.s

def printList(L):
    if len(L) == 0:
	print "[]"
    else:
        listString = "["
        listString += ", ".join(["%s" %x for x in L])
	listString += "]"
        print listString

time1 = Time(12)
time2 = Time(3456)
time3 = Time(91)

alist = [time1, time2, time3]
printList(alist)