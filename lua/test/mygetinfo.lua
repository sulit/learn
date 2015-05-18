#!/usr/bin/lua

local debug = debug
local print = print
local pairs = pairs
module("mygetinfo")

__file__ = debug.getinfo(1, 'S').source:sub(2)
print(__file__)
local tb = debug.getinfo(1, 'S')
for k,v in pairs(tb) do
	print(k, v)
end
