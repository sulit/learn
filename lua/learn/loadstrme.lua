#!/usr/bin/lua

print "enter function to be plotted (with variable 'x'):"
local l = io.read()
local f = assert(loadstring("do return " .. l .. " end"))
print(f())
--[[
for i = 1, 20 do
	x = i
	print(string.rep("*", f()))
end
-]]
