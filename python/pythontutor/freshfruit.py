#!/usr/bin/python

def printa(a):
	for v in a:
		print(v,end='')
		print(' ',end='')
	print()
freshfruit = ['	banana', '	loanberry ', 'passion fruit ']
printa(freshfruit)
freshfruit1 = [weapon.strip() for weapon in freshfruit]
printa(freshfruit1)
twonum = [(x, x**2) for x in range(6)]
printa(twonum)
