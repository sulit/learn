#!/usr/bin/lua

local file, msg

repeat
	print("enter a file name:")
	local name  = io.read()
	if not name then return end
	file = assert(io.open(name, "r"))
until file
