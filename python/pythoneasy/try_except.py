#!/usr/bin/python

import sys

try:
	s=raw_input('Enter something-->')
except EOFError:
	print '\nWhy did you do an EOF on me?'
except:
	print '\nSome error/exception occurred.'

print 'Done'
