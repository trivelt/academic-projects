#!/usr/bin/python
from random import uniform
from math import log, e, factorial

import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np

LAMBDA = 1
N = 10000
debug = True
def debug(msg):
    if debug:
        print(msg)
        
def poisson(lmbd, k):
    return (lmbd**k * e**(-lmbd)) / factorial(k)
        
def draw_steps(x):
    y = list()
    for x_i in x:
        if y:
            y.append(y[-1]+1)
        else:
            y.append(1)
    plt.plot(x, y, drawstyle="steps")
    plt.show()
    
def draw_dots(y):
    x = range(len(y))
    plt.scatter(x, y)
    plt.show()
    
    
def draw_dots_with_theoretical(y):
    x = range(len(y))
    plt.scatter(x, y)

    y = [poisson(5, i) for i in x]
    plt.plot(x, y)

    plt.show()        

def random_time():
    lambda_1 = LAMBDA # /min
    u_i = uniform(0, 1)
    t_i = -log(u_i) / lambda_1
    return t_i
    
def get_number_of_events(events, time):
    if time > events[-1]:
        return 0
    for i in range(len(events)):
        if events[i] == time:
            return len(events[:i+1])
        elif events[i] > time:
            return len(events[:i])
    
if __name__ == "__main__":

    events_in_time = list()
    for j in range(N):
        events = list()
        for i in range(100):    
            t = random_time()
            if events:
                t = events[-1] + t
#            debug("Time=" + str(t))
            events.append(t)
            
        time = 5
        num_of_events = get_number_of_events(events, time)
        events_in_time.append(num_of_events)
#        debug("Liczba zdarzen w " + str(time) + " sekundzie: " + str(num_of_events))
        if j == 2:
            draw_steps(events)

    max_ev = max(events_in_time)
    events_stats = dict()
    for i in range(max_ev+1):
        events_stats[i] = 0
    for event in events_in_time:
         events_stats[event] += 1
            
#    draw_dots(events_stats.values())
    
    normalized_values = [val/float(N) for val in events_stats.values()]
    draw_dots_with_theoretical(normalized_values)

