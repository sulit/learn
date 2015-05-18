#!/usr/bin/python

def printMax(x, y):
	'''Prints the maxium of two numbers.

	The two values must be integers.'''
	x = int(x)
	y = int(y)

	if x > y:
		print x, 'is maxium'
	else:
		print y, 'is maxium'

printMax(11,1)
print printMax.__doc__
help(printMax)
