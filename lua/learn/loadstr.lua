#!/usr/bin/lua

require "io"

--f = loadstring("local a = 10; return a + 20")
l = io.read()
print(l)
f = loadstring(("return " .. l))
print(f())
