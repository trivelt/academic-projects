#!/usr/bin/python


line = "|...."

length = 20

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