#!/usr/bin/lua

--[[
require "myprint"

print("world")
--]]

--[[
local teststr = require "module_t"
print(teststr)

print("world")
--]]

--require("mygetinfo")
--print(mygetinfo.__file__)

--[[
local hello = "world",print("what")
print(hello)
--]]

--[[
local tb={}
local hello={}
tb.testtb=hello
hello.str="world"
for k,v in pairs(tb.testtb) do
	print(k,v)
end
--]]
--[[
local tb={}
local hello={}
tb.testtb=hello
hello.str="world"
--]]

--[[
a = {}
b = {__mode = "v"}
setmetatable(a,b)
key = {}
print(key)
a[key] = {["hello"] = "world"}
key = {}
print(key)
a[key] = {["hello"] = "world"}
collectgarbage()
for k,v in pairs(a) do
	print(k)
end
--]]

