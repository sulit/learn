#!/usr/bin/python

knights = {'gallahad':'the pure','robin':'the brave'}
for k, v in knights.items():
	print(k, v)
for i, v in enumerate(['tic', 'tac', 'toe']):
	print(i, v)
questions=['name', 'quest', 'favorite color']
answers=['lancelot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
	print('What is your {0}? It is {1}.'.format(q, a))
for i in reversed(range(1, 10, 2)):
	print(i)
basket=['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
for f in set(basket):
	print(f)
for f in sorted(set(basket)):
	print(f)
words=['cat', 'window', 'defenestrate']
for w in words[:]:
	if len(w) > 6:
		words.insert(0, w)
print(words)
