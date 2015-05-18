#!/usr/bin/lua

local t_t = {'a','b'}

local c = 0
for k,v in pairs(t_t) do
	print(k)
	c = c + 1
end
print("hello")
print(c)
