#============================================
#   Copyright (C) 2015 All rights reserved.
#
#   filename : fdfstest.py
#   author : sulit - sulitsrc@163.com
#   last modified : 2015-05-24 09:12
#   description :
#
#============================================

#!/usr/bin/python

import fdfspyclient

fdfspyclient.fdfs_init("client.conf")
#fdfspyclient.fdfs_upload("Makefile", None)
fdfspyclient.fdfs_download("group1",
		"M00/00/00/rBBXglVh1C6AKT87AAAD6VEwZK85530679", "haha")
