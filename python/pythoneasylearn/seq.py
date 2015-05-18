#!/usr/bin/python

shoplist = ['apple','mango','carrot','banana']

for i in range(0,4):
	print 'Item %d is %s'% (i, shoplist[i])

for i in (-1,-2):
	print 'Item %d is %s'% (i, shoplist[i])

print 'Item 1 to 3 is ', shoplist[1:3]
print 'Item 2 to end is ', shoplist[2:]
print 'Item 1 to -1 is ', shoplist[1:-1]
print 'Item start to end is ', shoplist[:]

name = "sulit"
print 'Item 1 to 3 is ', name[1:3]
print 'Item 2 to end is ', name[2:]
print 'Item 1 to -1 is ', name[1:-1]
print 'Item start to end is ', name[:]
