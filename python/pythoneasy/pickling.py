#!/usr/bin/python

import cPickle as p

shoplistfile = 'shoplist.data'

shoplist = ['apple', 'mango', 'carrot']

f = file(shoplistfile, 'w')
p.dump(shoplist, f)
f.close()

f=file(shoplistfile)
storedlist=p.load(f)
print storedlist
