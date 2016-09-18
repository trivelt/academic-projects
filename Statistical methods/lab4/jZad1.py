#!/usr/bin/python
from random import randint, choice, uniform, gauss
from math import e, pi, log, floor, ceil
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np

class GaussGenerator:
    def __init__(self):
        pass
        
    def generateGaussList(self, N):
        normals = list()
        while len(normals) != N:
            norm = self.generateNormal()
            if norm:
                normals.append(norm)
        return normals

    def generateNormal(self):
        x = uniform(-1, 1)
        y = uniform(-1,1)
        z = x**2 + y**2
        if z < 1:
            mi = x*(-2.0/z*log(z))**(1/2.0)
            return mi
        
    def generate(self, mi=0, sigmaKw=1):
        sigma = sigmaKw**(1/2.0)
        x = self.generateNormal()
        if x:
            y = x*sigma+mi
            return y
        
    def generateNormalList(self, N, mi=0, sigmaKw=1):
        normals = list()
        lengthOfSample = 0
        while len(normals) != N:
            norm = self.generate(mi, sigmaKw)
            if norm:
                normals.append(norm)
        return normals 
        
#    def generateUniformNumbersList(self, N):
#        numbers = list()
#        for i in range(N):
#            number = uniform(0, 1)
#            numbers.append(number)
#        return numbers
        
    def generateUniformNumbersList(self, N, minimum=0, maximum=1):
        numbers = list()
        for i in range(N):
            number = uniform(minimum, maximum)
            numbers.append(number)
        return numbers    
        
class StatisticalTests:
    def __init__(self):
        pass
        
           
    def chiKwadrat(self, sample, step):
        classesDict = self.createClassesDict(sample, step, 0, 1.0)
        numberOfClasses = len(classesDict)

        suma = 0
        for cl in classesDict:
            val = classesDict[cl]
            suma += val
#        print "Liczb w przedzialach: ", suma        
        
        sumForResult = 0
        for num_range in classesDict:
            value = classesDict[num_range]
            npi = len(sample) / float(numberOfClasses)
            sumForResult += ((value-npi)**2)/npi
        return sumForResult
        
    def chiKwadratNpi(self, sample, step, npi):
        classesDict = self.createClassesDict(sample, step, -3.0, 3.0)
        numberOfClasses = len(classesDict)
        
        sumForResult = 0
        i = 0
        for num_range in classesDict:
            value = classesDict[num_range]
            sumForResult += ((value - npi[i] * len(sample))**2) / (npi[i] * len(sample))
            i += 1
#        print "Result", sumForResult
        return sumForResult
        
    def createClassesDict(self, sample, numberOfClasses, minRange, maxRange):
        numbersRange = abs(maxRange-minRange) 
        step =  numbersRange / numberOfClasses
        classesInfoDict = dict()        
        classesDict = dict()
        num = minRange
        for x in range(numberOfClasses):
            classesDict[x] = 0
            downNum = num
            upNum = num + step
            classesInfoDict[x] = (downNum, upNum)
            num = upNum
        for number in sample:
            for elem in classesInfoDict:
                downNum, upNum = classesInfoDict[elem]
                if number >= downNum and number < upNum:
                    classesDict[elem] += 1
                    break
        teorNumInEachClass = len(sample)/float(numberOfClasses)
        return classesDict  

losowanie = 10000
generator = GaussGenerator()
statTests = StatisticalTests()

n = 20
smaller = 0
for i in range(losowanie):
    nums = generator.generateUniformNumbersList(n)
    chiKw = statTests.chiKwadrat(nums, 3)
    if chiKw < 10.117:
        smaller += 1
print("dla n = " + str(n) + " wynik = " + str(smaller/float(losowanie)))


smaller = 0
n = 100
for i in range(losowanie):
    nums = generator.generateUniformNumbersList(n)
    chiKw = statTests.chiKwadrat(nums, 10)
    if chiKw < 77.04:
        smaller += 1
print("dla n = " + str(n) + " wynik = " + str(smaller/float(losowanie)))

print("=======================================")

smaller = 0
n = 20
probabilities = (0.15731, 0.68268, 0.15731)
for i in range(losowanie):
    nums = generator.generateUniformNumbersList(n, -3, 3)
    chiKw = statTests.chiKwadratNpi(nums, 3, probabilities)
    if chiKw < 10.117:
        smaller += 1
print("dla n = " + str(n) + " [-3, 3] - wynik = " + str(smaller*100/float(losowanie)))



smaller = 0
n = 100
probabilities = (0.008065, 0.02773, 0.07914, 0.15918, 0.22575, 0.22575, 0.15918, 0.07914, 0.02773, 0.008065)
for i in range(losowanie):
    nums = generator.generateUniformNumbersList(n, -3, 3)
    chiKw = statTests.chiKwadratNpi(nums, 10, probabilities)
    if chiKw < 77.04:
        smaller += 1
print("dla n = " + str(n) + " [-3, 3] - wynik = " + str(smaller*100/float(losowanie)))







smaller = 0
n = 100
probabilities = (0.008065, 0.02773, 0.07914, 0.15918, 0.22575, 0.22575, 0.15918, 0.07914, 0.02773, 0.008065)
classesDict = dict()

for i in range(losowanie):

    for x in range(10):
        classesDict[x] = 0
    sample = generator.generateUniformNumbersList(n, -3, 3)
    for number in sample:
        if number < (-2.4):
            classesDict[0] += 1
        elif number >= (-2.4) and number < (-1.8):
            classesDict[1] += 1
        elif number >= (-1.8) and number < (-1.2):
            classesDict[2] += 1            
        elif number >= (-1.2) and number < (-0.6):
            classesDict[3] += 1
        elif number >= (-0.6) and number < (0.0):
            classesDict[4] += 1
        elif number >= (0.0) and number < (0.6):
            classesDict[5] += 1
        elif number >= (0.6) and number < (1.2):
            classesDict[6] += 1
        elif number >= (1.2) and number < (1.8):
            classesDict[7] += 1
        elif number >= (1.8) and number < (2.4):
            classesDict[8] += 1
        else:
            classesDict[9] += 1                                                                                                

        
        chiKw = 0
        i = 0
        for num_range in classesDict:
            value = classesDict[num_range]
            chiKw += ((value - probabilities[i] * len(sample))**2) / (probabilities[i] * len(sample))
            i += 1


    if chiKw < 77.04:
        smaller += 1
print("dla n = " + str(n) + " [-3, 3] - wynik = " + str(smaller*100/float(losowanie)))
