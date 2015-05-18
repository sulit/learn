#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
t = 12345, 54321, 'hello!'
print(t)
printa(t)
print(t[0])
u = t, (1, 2, 3, 4, 5)
printa(u)
v = [[1, 2, 3], [3, 2, 1]]
printa(v)
empty = ()
singleton = 'hello',
print(len(empty))
print(len(singleton))
x, y, z = t
print(x)
print(y)
print(z)
