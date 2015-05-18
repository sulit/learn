#!/usr/bin/lua

print "enter your experession:"
local l = io.read()
local func = assert(loadstring("return " .. l))
print("the value of your expression is " .. func())
