#!/usr/bin/python

import os

tar_command = 'od if.py > if.bin'

if os.system(tar_command) == 0:
	print 'Successful ',tar_command
else:
	print 'Backup FAILED'
