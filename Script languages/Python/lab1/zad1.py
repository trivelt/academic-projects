#!/usr/bin/python
# Maciej Michalec, grupa 2
import sys

try:
    granica = int(argv[1]) + 1
except:
    print "Blad"
    sys.exit(1)

for i in range(1, granica):
    for j in range(1, granica):
        print i * j, " "
