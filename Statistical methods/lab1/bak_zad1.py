#!/usr/bin/python
from random import randint, choice, uniform, gauss
from math import e, pi, log
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np


def draw_histogram(histogram):
    plt.hist(histogram, facecolor="#eeefff", normed=True, bins=1000)
    plt.plot()
    plt.show()
    
def draw_histograms(histogram1, histogram2):
    plt.hist(histogram1, facecolor='green', normed=True, bins=1000)
    plt.hist(histogram2, normed=True, bins=1000)
    plt.plot()
    plt.show()    
    
def draw_histogram_with_theoretical(histogram):
    plt.hist(histogram, normed=True, bins=100)
    x = np.linspace(-5,5,100)
#    plt.plot(x, mlab.normpdf(x, 0, 1))
    y = normal(x)
    plt.plot(x, y)
    plt.show()    

def normal(x):
    sigma=3.0
    sigmaKw = sigma**2
    mi = 2.0
    norm = (1.0/(((2* pi)**(1/2.0))*sigma))*e**((-(x-mi)**2)/(2*sigmaKw))
    return norm
    
def draw_normal():
    x = np.linspace(-15,15,100) # 100 linearly spaced numbers
    y = normal(x) # computing the values of sin(x)/x
    plt.plot(x,y)
#    for x in range(-100, 100):    
#        plt.plot(normal(x))
    plt.show()

def getGaussianRandomNumbersList(N):
    L = list()
    for i in range(N):
	rNumber = round(gauss(100,30))
	L.append(int(rNumber))
    return L

class GaussGenerator:
    def __init__(self):
        pass
        
    def generateGaussList(self, N):
        normals = list()
        for i in range(N):
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
        for i in range(N):
            norm = self.generate(mi, sigmaKw)
            if norm:
                normals.append(norm)
        return normals 
        
        
generator = GaussGenerator()
#draw_normal()
#hist_to_draw = generator.generateNormalList(100000)
hist_to_draw2 = generator.generateNormalList(100000, 2, 9)


draw_histogram_with_theoretical(hist_to_draw2)
#draw_histogram(hist_to_draw)

#draw_histograms(hist_to_draw, hist_to_draw2)


#N = 1000
#print("Generowanie liczb")
#generator = GaussGenerator()
#histogram = dict()
#for i in range(100):
#    histogram[i] = 0

#for i in range(N):
#    randNum = generator.generate()
#    histogram[round(randNum*100)] += 1
    
#    print randNum*100
    
#for element in histogram:
#    print element, histogram[element]


#hist_to_draw = list()
#for elem in histogram:
#    powt = histogram[elem]
#    for i in range(powt):
#        hist_to_draw.append(elem)

#print histogram.values()    

#hist_to_draw = generator.generateN()
#draw_histogram(hist_to_draw)

#hist_to_draw = generator.generateNormalList(100000)
#draw_histogram(hist_to_draw)

#hist_to_draw=getGaussianRandomNumbersList(10000)
#draw_histogram(hist_to_draw)


