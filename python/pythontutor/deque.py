#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
from collections import deque
queue = deque(["Eric","John","Michael"])
printa(queue)
queue.append("Terry")
printa(queue)
queue.append("Graham")
printa(queue)
print(queue.popleft())
print(queue.popleft())
printa(queue)
