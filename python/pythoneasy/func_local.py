#!/usr/bin/python

def myfunc(x):
	print 'x is', x
	x = 2
	print 'Change local x to', x

x =5
myfunc(x)
print 'x is still', x
