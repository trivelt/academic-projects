#!/usr/bin/python

class Edge:
	"""Klasa reprezentuje krawedz grafu"""

	def __init__(self, x, y):
		if x is y:
			raise Exception("Podano dwa takie same argumenty")
		self.a = x
		self.b = y

	def __str__(self):
		return str(self.a) + "->" + str(self.b)


import unittest
class TestEdge(unittest.TestCase):

	def setUp(self): pass

	def test_init(self):
		kr = Edge(1, 2)
		self.assertEqual(kr.a, 1)
		self.assertEqual(kr.b, 2)
		self.assertRaises(Exception, Edge, 3, 3)

	def test_str(self):
		krawedz = Edge(2,5)
		self.assertEqual(krawedz.__str__(), "2->5")

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()

