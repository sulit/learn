#!/usr/bin/python

basket = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
print(basket)
print('orange' in basket)
print('craggrass' in basket)

a = set('abracadabra')
print(a)
b = set('alacazam')
print(b)
print(a - b)
print(a | b)
print(a & b)
print(a ^ b)

a = { x for x in 'abracadabra' if x not in 'abc'}
print(a)
