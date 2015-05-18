#!/usr/bin/lua

local function myprint()
	local i = 1
	return function ()
		print(i)
	end
end

myprint()
local myclo = myprint()
myclo()
