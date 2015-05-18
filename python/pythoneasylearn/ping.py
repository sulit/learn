#!/usr/bin/python

import os

clean_file_cmd="rm -rf ping_result.txt"
os.system(clean_file_cmd)
for i in range(1,5):
	ping_cmd="ping -c 4 "+"192.168.2."+str(i)+" >>ping_result.txt 2>> ping_result.txt"
	os.system(ping_cmd)
