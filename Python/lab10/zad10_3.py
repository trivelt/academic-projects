#!/usr/bin/python

class Stack:
	def __init__(self, size):
		self.max_size = size
		self.tab = list()
		self.numbers = dict()

	def push(self, item):
		if len(self.tab) >= self.max_size:
			raise Exception("Stack is full, can't push item " + str(item));
		if item in self.numbers:
			raise Exception("The item " + str(item) + " is already in stack")
		else:
			self.tab.append(item)
			self.numbers[item] = 1


	def pop(self):
		if len(self.tab) == 0:
			raise Exception("Stack is empty")
		item = self.tab.pop()
		self.numbers.pop(item)
		return item


import unittest

class TestStack(unittest.TestCase):

	def setUp(self): pass

	def test_push_full(self):
		stos = Stack(2)
		stos.push(5)
		stos.push(7)
		self.assertRaises(Exception, stos.push, 9)
		drugiStos = Stack(1)

	def test_push_double_elements(self):
		stos = Stack(4)
		stos.push(6)
		self.assertRaises(Exception, stos.push, 6)

	def test_pop_empty(self):
		stos = Stack(5)
		self.assertRaises(Exception, stos.pop)
		stos.push(1)
		stos.pop()
		self.assertRaises(Exception, stos.pop)

	def test_push_pop(self):
		stos = Stack(6)
		stos.push(67)
		stos.push(44)
		self.assertEqual(stos.pop(), 44)		
		self.assertEqual(stos.pop(), 67)		
		stos.push(1)
		stos.push(9)
		stos.push(10)
		self.assertEqual(stos.pop(), 10)

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()

