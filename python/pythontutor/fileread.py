#!/usr/bin/python
if False:
	f = open('workfile','r')
	#print(f.read())
	#print(f.read())
	#print(f.readline(),end='')
	for line in f:
		print(line, end='')

with open('workfile', 'r') as f:
	read_data = f.read()
	print(read_data, end='')

print(f.closed)
