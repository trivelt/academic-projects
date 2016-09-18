#!/usr/bin/python

def odwracanie(L, left, right):
    while left < right:
	temp = L[left]
	L[left] = L[right]
	L[right] = temp
	left += 1
	right -= 1

def odwracanie_rek(L, left, right):
    if left < right:
	temp = L[left]
	L[left] = L[right]
	L[right] = temp
	odwracanie_rek(L, left+1, right-1)

lista = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
print lista
odwracanie(lista, 2, 7) # czyli od 3 do 8
print lista
odwracanie_rek(lista, 8,11) # czyli od 9 do 12
print lista