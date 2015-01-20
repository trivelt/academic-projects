#!/usr/bin/python
from node import Node

class Graph:
	"""
	Klasa reprezentuje graf w postaci listy sasiedztwa
	(lista list)
	"""
	def __init__(self, n):
		self.numberOfNodes = n
		self.nodes = [Node(i) for i in range(n)]

	def get_node(self, i):
		""" Funkcja zwraca wierzcholek o i-tym indeksie """ 
		if i < 0 or i >= self.numberOfNodes:
			raise Exception("Zly indeks")
		return self.nodes[i]

	def add_edge(self, i, j):
		"""" Funkcja dodaje krawedz od wezla o indeksie i
			do wezla o indeksie j """
		if i < 0 or j < 0 or i >= self.numberOfNodes or j >= self.numberOfNodes:
			raise Exception("Zly indeks")
		firstNode = self.get_node(i)
		secondNode = self.get_node(j)
		firstNode.add_neighbour(secondNode)
		secondNode.add_neighbour(firstNode)

	def __str__(self):
		""" Funkcja wyswietla graf jako liste sasiedztwa """
		text = "\nLista sasiedztwa grafu:\n"
		for node in self.nodes:
			text += str(node.data) + ": "
			for neighbour in node.neighbours:
				text += str(neighbour.data)
				if neighbour.data != node.neighbours[len(node.neighbours)-1].data:
					text += ", "
			text += "\n"
		return text


	def dfs(self, v):
		""" Funkcja przeglada graf algorytmem DFS
			zaczynajac od wierzcholka o indeksie v """
		pass


	def bfs(self, v):
		""" Funkcja przeglada graf algorytmem BFS
			zaczynajac od wierzcholka o indeksie v """
		pass


import unittest
class TestGraph(unittest.TestCase):

	def setUp(self):
		self.graf = Graph(7)

	def test_init(self):
		self.assertEqual(self.graf.numberOfNodes, 7)

	def test_get_node(self):
		self.assertEqual(self.graf.get_node(4).data, 4)
		self.assertRaises(Exception, self.graf.get_node, 8)
		self.assertRaises(Exception, self.graf.get_node, -1)

	def test_add_edge(self):
		self.graf.add_edge(0,4)
		self.graf.add_edge(0,1)
		neighbour = self.graf.get_node(0).neighbours[1]
		self.assertTrue(self.graf.get_node(1) in self.graf.get_node(0).neighbours)
		self.assertEqual(neighbour.data, 4)
		self.assertRaises(Exception, self.graf.add_edge, 1, 8)

	def test_str(self):
		g = Graph(3)
		m = g.get_node(0)
		n = g.get_node(1)
		o = g.get_node(2)
		m.add_neighbour(n)
		m.add_neighbour(o)
		o.add_neighbour(m)
		text = "\nLista sasiedztwa grafu:\n0: 1, 2\n1: \n2: 0\n"
		self.assertEqual(g.__str__(), text)

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()

