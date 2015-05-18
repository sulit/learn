#!/usr/bin/lua

local teststr = "%21%22%23%24%30"
local function __chrdec (hex)
	return string.char(tonumber(hex, 16))
end

local printstr = teststr:gsub("%%([0-9][0-9])", __chrdec)
print(printstr)
