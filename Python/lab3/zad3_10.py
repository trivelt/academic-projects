#!/usr/bin/python
import re

romanDict = {"I":1, "V":5, "X":10, "C":100, "D":500, "M":1000}
romanNumber = "MCMXCIII"
arabicNumber = 0
previousNumber = romanDict[romanNumber[0]]
pattern = r"^(M{0,3})(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"

if re.search(pattern, romanNumber) is not None:
	parts = re.findall(pattern, romanNumber)[0]
	if parts[0] != "":
		arabicNumber += romanDict[parts[0][0]]*len(parts[0])
	if parts[1] != "":
		if parts[1] == "CM":
			arabicNumber += 900
		elif parts[1] == "CD":
			arabicNumber += 400
		else:
			numList = [romanDict[x] for x in parts[1]]
			arabicNumber += sum(numList)
	if parts[2] != "":
		if parts[2] == "XC":
			arabicNumber += 90
		elif parts[2] == "XL":
			arabicNumber += 40
		else:
			numList = [romanDict[x] for x in parts[2]]
			arabicNumber += sum(numList)
	if parts[3] != "":
		if parts[3] == "IX":
			arabicNumber += 9
		elif parts[3] == "IV":
			arabicNumber += 4
		else:
			numList = [romanDict[x] for x in parts[3]]
			arabicNumber += sum(numList)		
	print romanNumber,"=",arabicNumber
else:
	print "Invalid roman number"		