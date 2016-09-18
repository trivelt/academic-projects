#!/usr/bin/python
# Maciej Michalec, grupa 2

def is_correct_mark(mark):
    value = 0
    if mark.startswith("+") or mark.startswith("-"):
        try:
            value = float(mark[1:])
            value += 0.25 if mark.startswith("+") else (-0.25)
            return True, value
        except:
            return False, "Error"
    elif mark.endswith("+") or mark.endswith("-"):
        try:
            value = float(mark[:-1])
            value += 0.25 if mark.endswith("+") else (-0.25)
            return True, value
        except:
            return False, "Error"
    else:
        try:
            value = float(mark)
            return True, value
        except:
            return False, "Error"
            
def normalize_name(name):
    name = name[0].upper() + name[1:].lower()
    return name
