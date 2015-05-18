#!/usr/bin/lua

local t = {}
print(type(t))
if type(t) == "table" then
	print("t is a table")
end
t.test = "yes"
print("hi,"..t.test)
