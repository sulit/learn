#!/usr/bin/python

print 'Simple Assignment'

shoplist = ['apple','mango','carrot','banana']
mylist = shoplist

del shoplist[0]

print 'shoplist is', shoplist
print 'mylist is', mylist

mylist = shoplist[:]

del mylist[0]

print 'shoplist is', shoplist
print 'mylist is', mylist
