#!/usr/bin/python
from fractions import gcd

def normalize(frac): # normalization using greatest commons divisor 
	divisor = gcd(frac[0], frac[1])
	return [frac[0]/divisor, frac[1]/divisor]

def add_frac(frac1, frac2):        # frac1 + frac2
	newFrac = [0, 0]
	newFrac[0] = frac1[0]*frac2[1] + frac2[0]*frac1[1]
	newFrac[1] = frac1[1]*frac2[1]
	return normalize(newFrac)

def sub_frac(frac1, frac2):        # frac1 - frac2
	newFrac = [0, 0]
	newFrac[0] = frac1[0]*frac2[1] - frac2[0]*frac1[1]
	newFrac[1] = frac1[1]*frac2[1]
	return normalize(newFrac)

def mul_frac(frac1, frac2):        # frac1 * frac2
	newFrac = [0, 0]
	newFrac[0] = frac1[0]*frac2[0]
	newFrac[1] = frac1[1]*frac2[1]
	return normalize(newFrac)

def div_frac(frac1, frac2):        # frac1 / frac2
	return mul_frac(frac1, [frac2[1], frac2[0]])

def cmp_frac(frac1, frac2):        # -1 | 0 | +1
	frac1_f = frac2float(frac1)
	frac2_f = frac2float(frac2)
	if frac1_f > frac2_f:
		return 1
	elif frac1_f < frac2_f:
		return -1
	else:
		return 0


def is_positive(frac):       # bool, czy dodatni
	if frac2float > 0:
		return True
	else:
		return False

def is_zero(frac):                 # bool, typu [0, x]
	if frac[0] == 0:
		return True
	else:
		return False

def frac2float(frac):              # konwersja do float
	if frac[1] == 0:
		raise ZeroDivisionError
	return frac[0]/(float)(frac[1])

f1 = [-1, 2]                  # -1/2
f2 = [0, 1]                   # zero
f3 = [3, 1]                   # 3
f4 = [6, 2]                   # 3 (niejednoznacznosc)
f5 = [0, 2]                   # zero (niejednoznacznosc)

import unittest

class TestFractions(unittest.TestCase):

    def setUp(self): pass

    def test_add_frac(self):
        self.assertEqual(add_frac([1, 2], [1, 3]), [5, 6])
	self.assertEqual(add_frac([3, 4], [2, 6]), [13, 12])

    def test_sub_frac(self):
	self.assertEqual(sub_frac([3, 5], [2, 4]), [1, 10])
	self.assertEqual(sub_frac([7, 12], [3, 6]), [1, 12])

    def test_mul_frac(self):
	self.assertEqual(mul_frac([5, 7], [2, 3]), [10, 21])
	self.assertEqual(mul_frac([7, 3], [3, 6]), [7, 6])

    def test_div_frac(self):
	self.assertEqual(div_frac([18, 5], [6, 10]), [6, 1])
	self.assertEqual(div_frac([5, 10], [2, 3]), [3, 4])

    def test_cmp_frac(self):
	self.assertEqual(cmp_frac([1, 2], [3, 5]), -1)
	self.assertEqual(cmp_frac([10, 9], [6, 23]), 1)
	self.assertEqual(cmp_frac([1, 2], [7, 14]), 0)

    def test_is_positive(self):
	self.assertTrue(is_positive([1, 3]), True)
	self.assertTrue(is_positive([-4, 7]), False)
	self.assertTrue(is_positive([2, -2]), False)

    def test_frac2float(self):
	self.assertEqual(frac2float([8, 4]), 2.0)
	self.assertEqual(frac2float([7, 14]), 0.5)
	self.assertEqual(type(frac2float([2, 1])), type(1.0))
	self.assertRaises(ZeroDivisionError, frac2float, [5, 0])

    def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy
