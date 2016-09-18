#!/usr/bin/python

class Point:
    """Klasa reprezentujaca punkty na plaszczyznie."""

    def __init__(self, x=0, y=0):  # konstuktor
        self.x = x
        self.y = y

    def __str__(self):
	return "(" + str(self.x) + ", " + str(self.y) + ")"

    def __repr__(self):
	return "Point(" + str(self.x) + ", " + str(self.y) + ")"

    def __eq__(self, other):
	if self.x == other.x and self.y == other.y:
		return True
	else:
		return False

    def __ne__(self, other):        # obsluga point1 != point2
        return not self == other

class Rectangle:
    """Klasa reprezentujaca prostokat na plaszczyznie."""

    def __init__(self, x1=0, y1=0, x2=0, y2=0):
        self.pt1 = Point(x1, y1)
        self.pt2 = Point(x2, y2)
    def __str__(self):         # "[(x1, y1), (x2, y2)]"
	return "[" + str(self.pt1) + ", " + str(self.pt2) + "]"

    def __repr__(self):        # "Rectangle(x1, y1, x2, y2)"
	return "Rectangle(" + str(self.pt1.x) + ", " + str(self.pt1.y) + ", " + str(self.pt2.x) + ", " + str(self.pt2.y) + ")"

    def __eq__(self, other):    # obsluga rect1 == rect2
	if self.pt1 == other.pt1 and self.pt2 == other.pt2:
		return True
	else:
		return False

    def __ne__(self, other):        # obsluga rect1 != rect2
        return not self == other

    def center(self):           # zwraca srodek prostokata
	width = self.pt2.x - self.pt1.x
	height = self.pt2.y - self.pt1.y
	return Point(self.pt1.x+width/2.0,self.pt1.y+height/2.0)

    def area(self):            # pole powierzchni
	width = self.pt2.x - self.pt1.x
	height = self.pt2.y - self.pt1.y
	return width*height

    def move(self, x, y):      # przesuniecie o (x, y)
	self.pt1.x += x
	self.pt1.y += y

	self.pt2.x += x
	self.pt2.y += y
	return self
	
import unittest

class TestPoint(unittest.TestCase):

    def setUp(self): pass

    def test_str_point(self):
	self.assertEqual(str(Point(2, 3)), "(2, 3)")
	self.assertEqual(str(Point(8, 2)), "(8, 2)")

    def test_eq_point(self):
	a = Point(2,2)
	self.assertEqual(Point(2, 2), a)

    def test_ne_point(self):
	self.assertEqual(Point(1, 2) == Point(2, 1), False)	

    def tearDown(self): pass


class TestRect(unittest.TestCase):

    def setUp(self): pass

    def test_str_rect(self):
        self.assertEqual(str(Rectangle(1,2,3,4)), "[(1, 2), (3, 4)]")
        self.assertEqual(str(Rectangle(0,0,6,4)), "[(0, 0), (6, 4)]")

    def test_repr_rect(self):
        self.assertEqual(repr(Rectangle(1,2,3,4)), "Rectangle(1, 2, 3, 4)")
        self.assertEqual(repr(Rectangle(0,0,6,4)), "Rectangle(0, 0, 6, 4)")

    def test_eq_rect(self):
	self.assertEqual(Rectangle(0,0,5,9), Rectangle(0,0,5,9))
	self.assertEqual(Rectangle(1,1,3,3) == Rectangle(1,1,3,3), True)

    def test_ne_rect(self):
	self.assertEqual(Rectangle(0,0,5,9) == Rectangle(1,1,3,3), False)
	self.assertEqual(Rectangle(1,1,7,9) == Rectangle(0,0,2,2), False)

    def test_center_rect(self):
	self.assertEqual(Rectangle(0,0,2,2).center(), Point(1,1))
	self.assertEqual(Rectangle(0,0,3,6).center(), Point(1.5, 3))

    def test_area_rect(self):
	self.assertEqual(Rectangle(0,0,2,2).area(), 4)
	self.assertEqual(Rectangle(3,6,10,10).area(), 28)

    def test_move_rect(self):
        self.assertEqual(str(Rectangle(1,2,3,4).move(2,0)), "[(3, 2), (5, 4)]")
        self.assertEqual(str(Rectangle(1,3,8,15).move(6,8)), "[(7, 11), (14, 23)]")

    def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy
