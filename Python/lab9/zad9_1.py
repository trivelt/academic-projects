#!/usr/bin/python

class Node:
	def __init__(self, data=None, next=None):
		self.data = data
		self.next = next

	def __str__(self):
		return str(self.data)

	def __repr__(self):
		return "{" + str(self) + ", " + str(self.next) + "}"


def traverse(node):    # wersja iteracyjna
    while node:
        print node
        node = node.next

def insert_head(node, data):  # algorytm klasy O(1)
    return Node(data, node)

def insert_tail(node, data):  # algorytm klasy O(N)
    head = node
    last = None
    while node:
        last = node
        node = node.next
    if last is None:      # lista byla pusta
        return Node(data)
    else:                 # last jest ostatni
        last.next = Node(data)
        return head   # head sie nie zmieni

def remove_head(node):
	if node:
		return [node.next, node.data]
	else: # lista pusta
		return [None, None]


def remove_tail(node):
	head = node
	penultimate = None
	if not node: #lista pusta
		return [None, None]
	while node.next:
		penultimate = node
		node = node.next
	data = node.data
	if penultimate is None:
		return [None, data] # lista jednoelementowa
	return [head, data]
	

head = None                   # [], pusta lista
head = Node(3, head)          # [3]
head = Node(2, head)          # [2, 3]
head = Node(4, head)          # [4, 2, 3]
head = insert_tail(head, 10)  # [4, 2, 3, 10]
head = insert_head(head, 5)   # [5, 4, 2, 3, 10]

head, data = remove_tail(head)	  # [5, 4, 2, 3]
print [head, data]
traverse(head)

print "\n"

head, data =  remove_head(head)
print [head, data]
traverse(head)

# Przyklad z lista jednoelementowa oraz pusta
print "\n\n"
hd = None
hd = Node(1, hd)
hd, dt = remove_tail(hd)
print [hd, dt]
hd, dt = remove_head(hd)
traverse(hd)
print [hd, dt]
