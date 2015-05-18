#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
matrix = [
	[1, 2, 3, 4],
	[5, 6, 7, 8],
	[9, 10, 11, 12],
]

printa(matrix)
matrix1 = [[row[i] for row in matrix] for i in range(4)]
printa(matrix1)
transposed = []
for i in range(4):
	transposed.append([row[i] for row in matrix])
printa(transposed)
matrix2 = list(zip(*matrix))
printa(matrix2)
