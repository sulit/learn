#!/usr/bin/python

f = open('workfile', 'a')
f.write('This is a write test!\n')
f.close()
f = open('workfile', 'r')
for line in f:
	print(line, end='')
