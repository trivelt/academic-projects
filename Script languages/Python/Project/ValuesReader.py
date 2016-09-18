#!/usr/bin/python

def read_value(line):
    splittedLine = line.split("=")
    if len(splittedLine) == 2:
        return splittedLine[1].rstrip("\n")
    else:
        return None
