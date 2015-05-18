#!/usr/bin/python

import os

pwd=os.getcwd()
print(pwd)
os.chdir('/home/sulit')
print(os.getcwd())
os.chdir(pwd)
print(os.getcwd())
os.system('cal')
