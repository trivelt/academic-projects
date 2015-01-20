#!/usr/bin/python

import sys
from node import Node
from graph import Graph

if len(sys.argv) > 1:
	flag = sys.argv[1]
	if flag == "--help" or flag == "-h":
		print "\nPomoc\n"
	elif flag == "--version" or flag == "-v":
		print "v. 0.9"
	else:
		print "Bledny argument"
	sys.exit()

numberOfNodes = int(raw_input("Podaj liczbe wierzcholkow grafu: "))
numberOfEdges = int(raw_input("Podaj liczbe krawedzi: "))

graf = Graph(numberOfNodes)

print("Teraz podaj wszystkie krawedzie wpisujac:\nindeks jednego wezla\n[enter]\n"
	"indeks drugiego wierzcholka")
for i in range(numberOfEdges):
	a = int(raw_input())
	b = int(raw_input())
	graf.add_edge(a, b)
	print ">>Dodany!"
print graf

exit = False
while exit is not True:
	print "\nWybierz funkcje, ktorej chcesz uzyc: "
	print "1) wyswietl liste sasiedztwa"
	print "2) przegladnij graf algorytmem DFS"
	print "3) przegladnij graf algorytmem BFS"
	print "4) zakoncz program"
	choice = int(raw_input())
	if choice == 1:
		print graf
	elif choice == 2:
		startNode = int(raw_input("Podaj indeks wierzcholka, od ktorego "
			"nalezy zaczac przegladanie grafu:"))
		graf.dfs(startNode)
	elif choice == 3:
		startNode = int(raw_input("Podaj indeks wierzcholka, od ktorego "
			"nalezy zaczac przegladanie grafu:"))	
		graf.bfs(startNode)	
	elif choice == 4:
		exit = True
	else:
		print "Bledny wybor, sprobuj jeszcze raz"

