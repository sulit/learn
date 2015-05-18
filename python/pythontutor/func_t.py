#!/usr/bin/python

def f(a, L=[]):
	L.append(a)
	return L

print(f(1))
print(f(2))
print(f(3))

def F(b, A=None):
	if A is None:
		A = []
	A.append(b)
	return A

print(F(1))
print(F(2))
print(F(3))
