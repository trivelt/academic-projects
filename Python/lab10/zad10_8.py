#!/usr/bin/python
from random import choice

class Node:
	def __init__(self, data=None, next=None, previous=None):
		self.data = data
		self.next = next
		self.previous = previous

	def __str__(self):
		return str(self.data)

class Queue:
	def __init__(self):
		self.head = None
		self.tail = None
		self.items = dict()
		self.size = 0

	def is_empty(self):
		return not self.head

	def insert(self, data):
		node = Node(data)   
		if self.is_empty():
			self.head = self.tail = node
		else:                  
			node.next = self.tail
			self.tail.previous = node
			self.tail = node
		self.items[self.size] = node
		self.size += 1


	def get(self):
		randNumber = choice(list(self.items.keys())) #losuje klucz ze slownika
		randItem = self.items.pop(randNumber) #pobieram przyporzadkowany do klucza wezel
		if randItem.previous is not None:
			prev = randItem.previous
			prev.next = randItem.next
			randItem.next = prev
		data = randItem.data
		self.head = self.head.previous
		if self.is_empty():     
			self.tail = None
		return data

kolejka = Queue()
kolejka.insert(5)
kolejka.insert(44)
kolejka.insert(912)
kolejka.insert(800)
kolejka.insert(7)
print kolejka.get()
print kolejka.get()
print kolejka.get()
print kolejka.get()
print kolejka.get()
