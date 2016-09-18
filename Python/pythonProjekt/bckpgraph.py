#!/usr/bin/python
from node import Node
from Queue import Queue

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

	def clear(self):
		""" Funkcja usuwa wszystkie krawedzie grafu """
		for node in self.nodes:
			del node.neighbours[:]

	def dfs(self, v):
		""" Funkcja przeglada graf algorytmem DFS
			zaczynajac od wierzcholka o indeksie v """
		vNode = self.get_node(v)
		ret = list()
		stack = [vNode]
		visited = [False for i in range(self.numberOfNodes)]
		while len(stack) != 0:
			w = stack.pop()
			if visited[w.data] is False:
				visited[w.data] = True
				for neighbour in w.neighbours:
					if visited[neighbour.data] is False:
						stack.append(neighbour)
				ret.append(w.data)
		return ret

	def bfs(self, v):
		""" Funkcja przeglada graf algorytmem BFS
			zaczynajac od wierzcholka o indeksie v """
		ret = list()
		vNode = self.get_node(v)
		queue = Queue()
		visited = [False for i in range(self.numberOfNodes)]
		queue.put(vNode)
		visited[v] = True
		while not queue.empty():
			w = queue.get()
			ret.append(w.data)
			for neighbour in w.neighbours:
				if visited[neighbour.data] == False:
					visited[neighbour.data] = True
					queue.put(neighbour)
		return ret

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
		g.clear()
		g.add_edge(0,1)
		g.add_edge(2,1)
		text = "\nLista sasiedztwa grafu:\n0: 1\n1: 0, 2\n2: 1\n"
		self.assertEqual(g.__str__(), text)

	def test_clear(self):
		self.graf.add_edge(1,2)
		self.graf.add_edge(1,3)
		n2 = self.graf.get_node(2)
		n3 = self.graf.get_node(3)
		self.assertEqual(self.graf.get_node(1).neighbours, [n2, n3])
		self.graf.clear()
		self.assertEqual(self.graf.get_node(1).neighbours, [])

	def test_dfs(self):
		self.graf.add_edge(0,1)
		self.graf.add_edge(0,2)
		self.graf.add_edge(0,3)
		self.graf.add_edge(1,3)
		self.graf.add_edge(2,3)
		self.graf.add_edge(2,4)
		self.graf.add_edge(3,5)
		self.graf.add_edge(4,6)
		self.assertEqual(self.graf.dfs(0), [0,3,5,2,4,6,1])
		self.assertEqual(self.graf.dfs(5), [5,3,2,4,6,0,1])
		self.graf.clear()
		self.graf.add_edge(0,1)
		self.graf.add_edge(1,3)
		self.graf.add_edge(2,1)
		self.graf.add_edge(3,4)
		self.assertEqual(self.graf.dfs(0), [0,1,3,4,2])
		self.assertEqual(self.graf.dfs(2), [2,1,3,4,0])
		self.assertEqual(self.graf.dfs(3), [3,4,1,2,0])

	def test_bfs(self):
		self.graf.add_edge(0,1)
		self.graf.add_edge(1,3)
		self.graf.add_edge(2,1)
		self.graf.add_edge(3,4)
		self.assertEqual(self.graf.bfs(0), [0,1,2,3,4])
		self.graf.clear()
		self.graf.add_edge(0,1)
		self.graf.add_edge(0,3)
		self.graf.add_edge(0,4)
		self.graf.add_edge(0,6)
		self.graf.add_edge(1,2)
		self.graf.add_edge(1,5)
		self.graf.add_edge(2,3)
		self.graf.add_edge(2,4)
		self.graf.add_edge(2,5)
		self.graf.add_edge(2,6)
		self.graf.add_edge(3,5)
		self.graf.add_edge(4,6)
		self.assertEqual(self.graf.bfs(5), [5, 1, 2, 3, 0, 4, 6])

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()

