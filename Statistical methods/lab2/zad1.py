#!/usr/bin/python
from random import randint, choice, uniform, gauss
from math import e, pi, log, floor
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np

def sample_from_sample(N, sample):
    newSample = list()
    for i in range(N):
        element = choice(sample)
        newSample.append(element)
    return newSample

def generate_bootstrap(N, sample):
    length_of_sample = len(sample)
    samples = list()
    while len(samples) < N:
        newSample = sample_from_sample(length_of_sample, sample)
        if newSample not in samples:
            samples.append(newSample)
    return samples
    
def generate_bootstrap_set(N, sample):
#    print "Generating bootstrap set", N
    length_of_sample = len(sample)
    samples = set()
#    print "samples len", len(samples)
    while len(samples) < N:
        newSample = tuple(sample_from_sample(length_of_sample, sample))
        samples.add(newSample)
    return list(samples)

def draw_histogram(histogram, name=None):
    plt.figure(name)
    plt.hist(histogram, facecolor="#eeefff", normed=True, bins=1000)
    plt.plot()
#    plt.show()
    plt.draw()
    
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
        lengthOfSample = 0
        while len(normals) != N:
            norm = self.generate(mi, sigmaKw)
            if norm:
                normals.append(norm)
        return normals 
        

generator = GaussGenerator()

# wygenerowac np. 1000 probek 9-el., 25-el, dla kazdej z probek policzyc estymatory wart. oczek., wariancji i mediany
samples = list()
estimators_of_e = list()
estimators_of_var_1 = list()
estimators_of_var_2 = list()
estimators_of_med = list()
N = 300000
numbers_in_sample = 9
for i in range(N):
    sample = generator.generateNormalList(numbers_in_sample, 2, 9)
    samples.append(sample)

    mean = np.mean(sample)
    e_estimator = mean
    estimators_of_e.append(e_estimator)

    sum_e = 0
    for element in sample:
        sum_e += (element - mean)**2

    var_estimator_1 = (1.0/(numbers_in_sample-1)) * sum_e    
    estimators_of_var_1.append(var_estimator_1)
    
    var_estimator_2 = (1.0/numbers_in_sample) * sum_e
    estimators_of_var_2.append(var_estimator_2)    
    
    sorted_sample = sorted(sample)
    med_estimator = np.median(sorted_sample)
    estimators_of_med.append(med_estimator)
 
#draw_histogram(estimators_of_e, "estimators of E")
#draw_histogram(estimators_of_var_1, "First estimators of Var")
#draw_histogram(estimators_of_var_2, "Second estimators of Var")
#draw_histogram(estimators_of_med, "estimators of Med")

means = estimators_of_e
mean_of_means = np.mean(means)
bias_mean = mean_of_means - 2.0
print "Bias_e", bias_mean

var_mean = 0
means_sq_sum = 0
for mean in estimators_of_e:
    means_sq_sum += mean**2
var_mean = (1.0/N)*means_sq_sum - mean_of_means**2
#print 'samples', samples
#print 'estimators_of_var_1', estimators_of_var_1
#print 'means of means', mean_of_means
#print 'means sq sum', means_sq_sum
print "var_mean", var_mean




mean_of_var_estimators_1 = np.mean(estimators_of_var_1)
bias_var_1 = mean_of_var_estimators_1 - 9.0
print "Bias_var_1", bias_var_1
#print 'mean_of_var_estimators_1', mean_of_var_estimators_1

#print "Var_1", estimators_of_var_1
var_1_estimators_sq_sum = 0
for estimator in estimators_of_var_1:
    var_1_estimators_sq_sum += estimator**2
var_of_var_1_estimators = (1.0/N)*var_1_estimators_sq_sum - np.mean(estimators_of_var_1)**2
#print "var_of_var_1_estimators", var_of_var_1_estimators



#print "Var_2", estimators_of_var_2
mean_of_var_estimators_2 = np.mean(estimators_of_var_2)
bias_var_2 = mean_of_var_estimators_2 - 9.0
print "Bias_var_2", bias_var_2



mean_of_med_estimators = np.mean(estimators_of_med)
bias_of_med_estimators = mean_of_med_estimators - 2.0
print "Bias_med", bias_of_med_estimators



#####################################################################
print "################################################################"
bootstrapSample = generator.generateNormalList(numbers_in_sample, 2, 9)
print "bootstrap sample", bootstrapSample
N = 100000
#samples = list()
#for i in range(N):
#    sample = sample_from_sample(9, bootstrapSample)
#    samples.append(sample)
samples = generate_bootstrap_set(N, bootstrapSample)

estimators_of_e = list()
estimators_of_var_1 = list()
estimators_of_var_2 = list()
estimators_of_med = list()

for sample in samples:
    mean = np.mean(sample)
    e_estimator = mean
    estimators_of_e.append(e_estimator)

    sum_e = 0
    for element in sample:
        sum_e += (element - mean)**2

    var_estimator_1 = (1.0/(numbers_in_sample-1)) * sum_e    
    estimators_of_var_1.append(var_estimator_1)
    
    var_estimator_2 = (1.0/numbers_in_sample) * sum_e
    estimators_of_var_2.append(var_estimator_2)    
    
    sorted_sample = sorted(sample)
    med_estimator = np.median(sorted_sample)
    estimators_of_med.append(med_estimator)
    
 
#draw_histogram(estimators_of_e, "bootstrap estimators of E")
#draw_histogram(estimators_of_var_1, "bootstrap First estimators of Var")
#draw_histogram(estimators_of_var_2, "bootstrap Second estimators of Var")
#draw_histogram(estimators_of_med, "bootstrap estimators of Med")
#plt.show()


means = estimators_of_e
mean_of_means = np.mean(means)
bias_mean = mean_of_means - 2.0
print "Bias_e", bias_mean

var_mean = 0
means_sq_sum = 0
for mean in estimators_of_e:
    means_sq_sum += mean**2
var_mean = (1.0/N)*means_sq_sum - mean_of_means**2
print 'means of means', mean_of_means
print 'means sq sum', means_sq_sum
print "var_mean", var_mean



mean_of_var_estimators_1 = np.mean(estimators_of_var_1)
bias_var_1 = mean_of_var_estimators_1 - 9.0
print "Bias_var_1", bias_var_1

#print "Var_1", estimators_of_var_1
var_1_estimators_sq_sum = 0
for estimator in estimators_of_var_1:
    var_1_estimators_sq_sum += estimator**2
var_of_var_1_estimators = (1.0/N)*var_1_estimators_sq_sum - np.mean(estimators_of_var_1)**2
#print "var_of_var_1_estimators", var_of_var_1_estimators



#print "Var_2", estimators_of_var_2
mean_of_var_estimators_2 = np.mean(estimators_of_var_2)
bias_var_2 = mean_of_var_estimators_2 - 9.0
print "Bias_var_2", bias_var_2



mean_of_med_estimators = np.mean(estimators_of_med)
bias_of_med_estimators = mean_of_med_estimators - 2.0
print "Bias_med", bias_of_med_estimators



ordered_samples_and_t = list()
for i in range(len(samples)):
    ordered_samples_and_t.append( [estimators_of_e[i], samples[i]] )
ordered_samples_and_t = sorted(ordered_samples_and_t, key=lambda elem: elem[0])    
ordered_samples = [x for x,y in ordered_samples_and_t]

confidence = 0.95
alfa = 1-confidence
Q0_Index = int(floor(N * alfa / 2.0) + 1)
Q1_Index = int(floor(N * (1- alfa/2.0) ) + 1)
print Q0_Index
print Q1_Index
 
print "Przedzial ufnosci: [" + str(ordered_samples[Q0_Index]) + ", " + str(ordered_samples[Q1_Index]) + "]"
