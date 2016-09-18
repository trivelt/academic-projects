#!/usr/bin/python

class Node:

    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)

def visit(node):
	print node

def traverse_inorder(top, visit):
    if top is None:
        return
    traverse_inorder(top.left, visit)
    visit(top)
    traverse_inorder(top.right, visit)

def insert_bst(top, data):   # zwraca nowy korzen
    if top is None:
        return Node(data)
    if data < top.data:
        top.left = insert_bst(top.left, data)
    elif data > top.data:
        top.right = insert_bst(top.right, data)
    else:
        pass          # ignorujemy duplikaty
    return top            # bez zmian

def max_bst(top):
	if top is None:
		raise ValueError("Tree is empty")
	max_node = top
	while top.right:
		top = top.right
	return top	

def min_bst(top):
	if top is None:
		raise ValueError("Tree is empty")
	max_node = top
	while top.left:
		top = top.left
	return top	


bst = None
#print "Max=", max_bst(bst) #wyjatek - puste drzewo
bst = Node(1)
bst = insert_bst(bst, 5)
bst = insert_bst(bst, 7)
bst = insert_bst(bst, 3)
bst = insert_bst(bst, 2)
bst = insert_bst(bst, 4)
bst = insert_bst(bst, 6)
traverse_inorder(bst, visit)

print "Max =", max_bst(bst)
print "Min =", min_bst(bst)
