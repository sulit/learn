#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
vec = [-4, -2, 0, 2, 4]
printa(vec)
vec1 = [x*2 for x in vec]
printa(vec1)
vec2 = [x for x in  vec if x >= 0]
printa(vec2)
vec3 = [abs(x) for x in vec]
printa(vec3)

vec = [[1,2,3],[4,5,6],[7,8,9]]
printa(vec)
vec1 = [num for elem in vec for num in elem]
printa(vec1)
