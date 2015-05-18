#!/usr/bin/python

ab = {
	'Sulit':'123@163.com',
	'Mengyi':'meng.yi.xxx@gmail.com',
	'Fantong':'null@163.com'
}

print "Sulit's address is %s"% ab['Sulit'],

ab['Mengyi'] = 'meng.yi.null@gmail.com'

del ab['Fantong']

print '\nThere are %d contacts in th address-book\n'% len(ab),

for name,address in ab.items():
	print 'Contact %s at %s'% (name,address)

if 'Sulit' in ab:
	print"\nSulit's address is %s"% ab['Sulit'],

if ab.has_key('Sulit'):
	print"\nSulit's address is %s"% ab['Sulit'],
