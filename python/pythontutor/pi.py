#!/usr/bin/python

from math import pi

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()

echopi = [str(round(pi, i)) for i in range(1, 6)]
printa(echopi)
