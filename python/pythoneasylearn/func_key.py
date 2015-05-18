#!/usr/bin/python
#important这个比较异常，要谨记 

def myfunc(a, b = 5, c = 10):
	print 'a is', a, 'and b is', b, 'and c is', c

myfunc(3,7)
myfunc(25,c=24)
myfunc(c=50, a=100)
