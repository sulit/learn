#!/usr/bin/python
#不是很了解

def make_repeater(n):
	return lambda s:s*n

twice = make_repeater(2)

print twice('word')
print twice(5)
