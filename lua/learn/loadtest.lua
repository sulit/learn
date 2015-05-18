#!/usr/bin/lua

l = {"hello", "world"}

f = loadstring(("return " .. l))
print(f())
