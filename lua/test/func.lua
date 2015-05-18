#!/usr/bin/lua

local function hello (...)
	print(...)
end

local result = type(hello) == "function"

print(result)
