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
#fdfspyclient.fdfs_download("group1",
#		"M00/00/00/rBBXglVh1C6AKT87AAAD6VEwZK85530679", "haha")
#fdfspyclient.fdfs_upload("client.conf", None)
#fdfspyclient.fdfs_getmeta("group1", "M00/00/00/wKj_gVViexuAD3pmAAAFyIdOK3o58.conf")
#fdfspyclient.fdfs_setmeta("group1", "M00/00/00/wKj_gVViiTOAQhlyAAAD6VEwZK85172634", "O", "name=sulit,value=1")
#fdfspyclient.fdfs_query_servers("group1", "M00/00/00/wKj_gVViexuAD3pmAAAFyIdOK3o58.conf")
#fdfspyclient.fdfs_append_file("group1/M00/00/00/wKj_gVViwp6EKuegAAAAABbz_f40441178", "Makefile")
#fdfspyclient.fdfs_file_info("group1/M00/00/00/wKj_gVViwp6EKuegAAAAABbz_f40441178")
#fdfspyclient.fdfs_list_all_groups(None, None)
fdfspyclient.fdfs_list_all_groups(None, "group1")
fdfspyclient.fdfs_destroy()
#fdfspyclient.fdfs_upload("Makefile", None)
