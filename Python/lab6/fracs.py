#!/usr/bin/python
from fractions import gcd

class Frac:

	def __init__(self, x=0, y=1):
		self.x = x
		self.y = y

	def __repr__(self):        # zwraca "Frac(x, y)"
		ret = "Frac(" + str(self.x) + ", " + str(self.y) + ")"
		return ret


	def __str__(self):         # zwraca "x/y" lub "x" dla y=1
		if self.y == 1:
			return str(self.x)
		ret = str(self.x)+"/"+str(self.y)
		return ret

	def __add__(self, other):  # frac1+frac2
		newFrac = Frac(0, 0)
		newFrac.x = self.x*other.y + other.x*self.y
		newFrac.y = self.y*other.y
		return newFrac.normalize()

	def __sub__(self, other):  # frac1-frac2
		newFrac = Frac(0, 0)
		newFrac.x = self.x*other.y - other.x*self.y
		newFrac.y = self.y*other.y
		return newFrac.normalize()

	def __mul__(self, other):   # frac1*frac2
		newFrac = Frac(0, 0)
		newFrac.x = self.x*other.x
		newFrac.y = self.y*other.y
		return newFrac.normalize()

	def __div__(self, other):   # frac1/frac2
		return self * Frac(other.y, other.x)

	# operatory jednoargumentowe
	def __pos__(self):  # +frac
		return self
	def __neg__(self):  # -frac
		return Frac(-self.x, self.y)

	def __invert__(self):  # odwrotnosc: ~frac
		return Frac(self.y, self.x)

	def __cmp__(self, other):  # cmp(frac1, frac2)
		frac1_f = self.frac2float()
		frac2_f = other.frac2float()
		if frac1_f > frac2_f:
			return 1
		elif frac1_f < frac2_f:
			return -1
		else:
			return 0

	def normalize(self): # normalization using greatest commons divisor 
		divisor = gcd(self.x, self.y)
		return Frac(self.x/divisor, self.y/divisor)


	def is_positive(self):       # bool, czy dodatni
		if self.frac2float() > 0:
			return True
		else:
			return False

	def is_zero(self):                 # bool, typu [0, x]
		if frac.x == 0:
			return True
		else:
			return False

	def frac2float(self):              # konwersja do float
		if self.y == 0:
			raise ZeroDivisionError
		return self.x/(float)(self.y)

import unittest

class TestFract(unittest.TestCase):

    def setUp(self): pass

    def test_add_frac(self):
        self.assertEqual(Frac(1, 2) + Frac(1, 3), Frac(5, 6))
	self.assertEqual(Frac(3, 4) + Frac(2, 6), Frac(13, 12))

    def test_sub_frac(self):
	self.assertEqual(Frac(3, 5) - Frac(2, 4), Frac(1, 10))
	self.assertEqual(Frac(7, 12) - Frac(3, 6), Frac(1, 12))

    def test_mul_frac(self):
	self.assertEqual(Frac(5, 7) * Frac(2, 3), Frac(10, 21))
	self.assertEqual(Frac(7, 3) * Frac(3, 6), Frac(7, 6))

    def test_div_frac(self):
	self.assertEqual(Frac(18, 5) / Frac(6, 10), Frac(6, 1))
	self.assertEqual(Frac(5, 10) / Frac(2, 3), Frac(3, 4))

    def test_str_frac(self):
	self.assertEqual(str(Frac(1, 2)), "1/2")
	self.assertEqual(str(Frac(5, 1)), "5")		

    def test_repr_frac(self):
	self.assertEqual(repr(Frac(1, 2)), "Frac(1, 2)")
	self.assertEqual(repr(Frac(5, 1)), "Frac(5, 1)")	

    def test_cmp_frac(self):
	self.assertFalse(Frac(1, 2) == Frac(3, 5))
	self.assertTrue(Frac(10, 9) > Frac(6, 23))
	self.assertEqual(Frac(1, 2), Frac(7, 14))

    def test_is_positive(self):
	self.assertEqual(Frac(1, 3).is_positive(), True)
	self.assertEqual(Frac(-4, 7).is_positive(), False)
	self.assertEqual(Frac(2,-2).is_positive(), False)

    def test_frac2float(self):
	self.assertEqual(Frac(8, 4).frac2float(), 2.0)
	self.assertEqual(Frac.frac2float(Frac(7, 14)), 0.5)
	self.assertEqual(type(Frac.frac2float(Frac(2, 1))), type(1.0))

    def test_invert_frac(self):
	self.assertEqual(~Frac(2, 5), Frac(5, 2))
	self.assertEqual(~Frac(1, 2), Frac(2, 1))

    def test_pos_frac(self):
	self.assertEqual(+Frac(12, 3), Frac(12, 3))
	self.assertEqual(+Frac(4, 8), Frac(4, 8))

    def test_neg_frac(self):
	self.assertEqual(-Frac(1,9), Frac(-1, 9))
	self.assertEqual(-Frac(7,3), Frac(-7, 3))

    def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy
