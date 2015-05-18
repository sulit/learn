#!/usr/bin/lua

local function foo()
	print("hello")
end

local tb = debug.getinfo(foo)
for k,v in pairs(tb) do
	print(k,v)
end
