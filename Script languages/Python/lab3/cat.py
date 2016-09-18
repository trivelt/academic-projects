#!/usr/bin/python
# Maciej Michalec, grupa 2
import sys
import os

textchars = bytearray({7,8,9,10,12,13,27} | set(range(0x20, 0x100)) - {0x7f})
is_binary_string = lambda bytes: bool(bytes.translate(None, textchars))

numberingFiles = False
numberingTotal = False
verbose = False
forceBinary = False
endOfOptions = False
files = []

for arg in sys.argv[1:]:
    if not endOfOptions:
        if arg == "-n":
            numberingFiles = True
            numberingTotal = False
        elif arg == "-N":
            numberingTotal = True
            numberingFiles = False
        elif arg == "-v":
            verbose = True
        elif arg == "-f":
            forceBinary = True
        else:
            files.append(arg)
            endOfOptions = True
    else:
        files.append(arg)

totalCounter = 0
for FILE in files:
    linesCounter = 0
    if not os.path.isfile(FILE):
        sys.stderr.write(FILE + " is not a correct file\n")
    if is_binary_string(open(FILE, 'rb').read(1024)) and not forceBinary:
        sys.stderr.write("File " + FILE + " is not a text file\n")
        continue
    try:
        fd = open(FILE)
    except:
        sys.stderr.write("Cannot open file " + FILE + "\n")
        continue

    for line in fd:
        if line.startswith("#") and not verbose:
            totalCounter += 1
            linesCounter += 1
            continue
        if numberingFiles:
            sys.stdout.write(str(linesCounter) + ": " + line)
        elif numberingTotal:
            sys.stdout.write(str(totalCounter) + ": " + line)
        else:
            sys.stdout.write(line)
        totalCounter += 1
        linesCounter += 1
