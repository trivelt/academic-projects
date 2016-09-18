#!/usr/bin/python
from random import uniform, choice
from math import log, e



# M/M/4/INF
# lambda_a - sredni czas oczekiwania 
# Z rozkladu wykladniczego z parametrem lambda_a losujemy czas naplywania zadan
# lambda_si - 20 s. trwa srednie wykonywanie
# 1. Sprawdz prawo Lidla (Little'a)
#  -> M/D/4/INF
#  -> M/U/4/INF
#  -> M/M/1/INF (4 razy szybszy procesor)
#  -> M/M/1/INF
#
# t_w - dlugosc oczekiwania
# t_s - dlugosc przetwarzania zadania, na podsttawie lambda_s
# Xw + Xs - srednia liczba zadan w systemie

LAMBDA_A = 1/15.0 # seconds
LAMBDA_SI = 1/20.0 # seconds
debug = True
def debug(msg):
    if debug:
        print(msg)
        
def random_time(lmbd):
    u_i = uniform(0, 1)
    t_i = -log(u_i) / lmbd
    return t_i
    

class Processor(object):
    def __init__(self, name):
        self.name = name
        self.isBusy = False
    

class Server(object):
    def __init__(self, number_of_processors=4):
        self.processors = range(number_of_processors)
        self.freeProcessors = range(number_of_processors)
        
#        self.processors = list()
#        for i in range number_of_processors:
#            newProc = Processor(i)
#            self.processors.append(newProc)
#            self.freeProcessors.append(i)
            
    def getFreeProcessor(self):
        if not self.hasFreeProcessor():
            raise "There are no free processors"
        return choice(self.freeProcessors)
        
    def hasFreeProcessor(self):
        if self.freeProcessors:
            return True
        return False
        
    def useProcessor(self, nr_of_proc):
        self.freeProcessors.remove(nr_of_proc)
#        usingProc = self.processors[nr_of_proc]
#        usingProc.isBusy = True
        
    def releaseProcessor(self, nr_of_proc):
        self.freeProcessors.append(nr_of_proc)
#        proc = self.processors[nr_of_proc]
#        proc.isBusy = False

if __name__ == "__main__":
    server = Server()
    print server.hasFreeProcessor()
    f_p = server.getFreeProcessor()
    print f_p
    server.useProcessor(f_p)
    f_p = server.getFreeProcessor()
    print f_p
    server.useProcessor(f_p)
    f_p = server.getFreeProcessor()
    print f_p
    server.useProcessor(f_p)
    f_p = server.getFreeProcessor()
    print f_p
    server.useProcessor(f_p)
    
    server.releaseProcessor(f_p)
    f_p = server.getFreeProcessor()
    print f_p
    server.useProcessor(f_p)    
