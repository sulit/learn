#!/usr/bin/lua

local teststr = "hello"
local printstr =""

for i = 1, #teststr do
	print(printstr)
	printstr = printstr .. string.byte(teststr, i)
end
print(printstr)
