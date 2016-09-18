#!/usr/bin/python
# Maciej Michalec, grupa 2
import sys
import os
from SekretariatSzkoly import is_correct_mark, normalize_name

DEBUG=False

def debug(msg):
    if DEBUG:
        print(msg)
        
class StudentsGroup:
    def __init__(self, group_name):
        self.name = group_name
        self.students = list()
        
    def __repr__(self):
        text = "StudentsGroup '" +  self.name + "' ("
        for student in self.students:
            text += str(student) + "; "
        return text
    
    def find_student(self, name, surname):
        for student in self.students:
            if student.name == name and student.surname == surname:
                return student
        return None
        
    def add(self, student):
        debug("Dodawanie studenta " + str(student))
        debug("Before: " + str(self.students))
        self.students.append(student)
        debug("After: " + str(self.students))
        
    def mean(self):
        value = 0
        for student in self.students:
            value += student.mean()
        value = value / float(len(self.students))
        return value             

    def sort(self):
#        self.students = sorted(self.students)
        self.students.sort(key = lambda student: student.surname + student.name)

class Student:
    def __init__(self, name, surname, mark):
        self.name = name
        self.surname = surname
        self.marks = [mark]
        
    def __repr__(self):
        return "Student(" + self.name + ", " + self.surname + ", " + str(self.marks) + ")"
        
    def summary(self):
        return self.surname + " " + self.name + ": " + str(self.marks) + ": " + "{0:.2f}".format(self.mean())
        
    def mean(self):
        value = 0
        for mark in self.marks:
            value += mark
        value = value / float(len(self.marks))
        return value

if len(sys.argv) < 2:
    print("Za malo argumentow. Prosze nazwe lub nazwy plikow zawierajacych oceny studentow.")
    sys.exit(1)

files = sys.argv[1:]

groups = list()
for filename in files:
    try:
        fd = open(filename)
    except:
        print("Nie mozna otworzyc pliku '" + filename + "'")
        continue
        
    debug("Odczyt pliku '" + filename + "'")
    students_group = StudentsGroup(os.path.basename(filename))
    
    for line in fd:
        splitted_data = line.split()
        if len(splitted_data) != 3:
            debug("Blad przy odczycie linii '" + line + "'")
            continue
            
        name, surname, mark = splitted_data    
        success, mark_number = is_correct_mark(mark)
        name = normalize_name(name)
        surname = normalize_name(surname)
        if not success:
            debug("Bledna ocena: '" + mark + "'")
            continue
        
        student = students_group.find_student(name, surname)
        if student is None:
            student = Student(name, surname, mark_number)
            debug("Dodawanie nowego studenta " + str(student))            
            students_group.add(student)
        else:
            debug("Student " + str(student) + " ma dodawana nowa ocene: " + str(mark_number))
            student.marks.append(mark_number)
    
    groups.append(students_group)

for group in groups:
    group.sort()
    print("\n ==== " + group.name + " ====")
    for student in group.students:
        print(student.summary())
        
    print("Srednia grupy: " + "{0:.2f}".format(group.mean()))

