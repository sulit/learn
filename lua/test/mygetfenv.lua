#!/usr/bin/lua

local function printhello()
	print("hello")
end

local tb = getfenv(2)
for k,v in pairs(tb) do
	print(k, v)
end
