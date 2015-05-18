#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
a = [-1, 1, 66.25, 333, 333, 1234.5]
printa(a)
del a[0]
printa(a)
del a[2:4]
printa(a)
del a[:]
printa(a)
del a
print(type(a))#会提示错误，根据错误查看
