#!/usr/bin/python

#没怎么搞懂

pairs = [(1,'one'),(2,'two'),(3,'three'),(4,'four')]
pairs.sort(key=lambda pair:pair[1])
for k,v in pairs:
	print(k,v)
