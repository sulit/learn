#!/usr/bin/python

def myfunc():
	global x
	print 'x is', x
	x = 2
	print 'Change local x to', x

x =5
myfunc()
print 'x is still', x
