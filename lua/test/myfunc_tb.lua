#!/usr/bin/lua

local func,err = loadfile("./mymodule.lua")
--[[
local function printhello ()
	print("hello")
end

local tb = { printhello() }

for k,v in pairs(tb) do
	print(k,v)
end
--]]

local testtb = { func() }

for k,v in pairs(testtb) do
	print(k,v)
end
