#!/usr/bin/python

import os
import time

source = ['/home/sulit/src','/home/sulit/tmp']

target_dir = '/mnt/e/backup'

today = target_dir + time.strftime('%Y%m%d')

now = time.strftime('%H%M%S')

comment = raw_input('Enter a comment-->')

if len(comment) == 0:
	target = today + os.sep + now + '.tar.gz'
else:
	target = today + os.sep + now + '_' + comment.replace(' ', '_') + '.tar.gz'

if not os.path.exists(today):
	os.mkdir(today)
	print 'Successfully created directory', today

tar_command = 'tar -zcvf %s %s -X /home/sulit/src/hello.txt'%(target, ' '.join(source))

if os.system(tar_command) == 0:
	print 'Successful backup to',target
else:
	print 'Backup FAILED'
