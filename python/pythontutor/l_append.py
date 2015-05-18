#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()

a = [2,5]
printa(a)
a.append(3)
printa(a)
L=[1,4]
a.extend(L)
printa(a)
a.insert(0,0)
printa(a)
a.insert(len(a),10)
printa(a)
a.insert(0,-1)
printa(a)
a.remove(-1)
printa(a)
#a.pop([3])
a.pop()
printa(a)
a.index(3)
print(a.index(3))
a.append(3)
a.count(3)
printa(a)
a.sort()
printa(a)
a.reverse()
printa(a)
print(a.copy())
a.clear()
printa(a)
