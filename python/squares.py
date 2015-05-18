#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
squares = []
for x in range(10):
	squares.append(x**2)
printa(squares)
squares = []
squares = [x**2 for x in range(10)]
printa(squares)
squares = []
squares = [(x, y) for x in [1, 2, 3] for y in [3, 1, 4] if x != y]
printa(squares)
squares = []
squares = list(map(lambda x: x**2, range(10)))
printa(squares)
