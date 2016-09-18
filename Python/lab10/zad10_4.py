#!/usr/bin/python

class Queue:
	def __init__(self, size=5):
		self.n = size + 1         # faktyczny rozmiar tablicy
		self.items = self.n * [None] 
		self.head = 0           # pierwszy do pobrania 
		self.tail = 0           # pierwsze wolne

	def is_empty(self):
		return self.head == self.tail

	def is_full(self):
		return (self.head + self.n-1) % self.n == self.tail

	def put(self, data):
		if self.is_full():
			raise Exception("Queue is full")
		self.items[self.tail] = data
		self.tail = (self.tail + 1) % self.n

	def get(self):
		if self.is_empty():
			raise Exception("Queue is empty")
		data = self.items[self.head]
		self.items[self.head] = None      # usuwam referencje
		self.head = (self.head + 1) % self.n
		return data

import unittest

class TestQueue(unittest.TestCase):

	def setUp(self): pass

	def test_queue_empty(self):
		kolejka = Queue(3)
		self.assertEqual(kolejka.is_empty(), True)
		kolejka.put(1)
		self.assertEqual(kolejka.is_empty(), False)

	def test_queue_full(self):
		kolejka = Queue(2)
		kolejka.put(54)
		self.assertEqual(kolejka.is_full(), False)
		kolejka.put(11)
		self.assertEqual(kolejka.is_full(), True)

	def test_queue_put(self):
		kolejka = Queue(1)
		kolejka.put(6)
		self.assertRaises(Exception, kolejka.put, 4)

	def test_queue_get(self):
		kolejka = Queue(3)
		self.assertRaises(Exception, kolejka.get)		
		kolejka.put(3)
		kolejka.put(77)
		self.assertEqual(kolejka.get(), 3)
		kolejka.put(6)
		kolejka.put(0)
		self.assertEqual(kolejka.get(), 77)

	def test_queue_full_empty(self):
		kolejka = Queue(0)
		self.assertEqual(kolejka.is_empty(), True)
		self.assertEqual(kolejka.is_full(), True)
		self.assertRaises(Exception, kolejka.get)				
		self.assertRaises(Exception, kolejka.put, 1)

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()
