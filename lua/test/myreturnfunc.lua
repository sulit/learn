#!/usr/bin/lua

local function returnf(str)
	return function()
		print(str)
	end
end

returnf("hello")
--runfunc = returnf
--runfunc("hello")
