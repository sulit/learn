#!/usr/bin/lua

--[[
--local status, err = pcall(function () error({ code = 121 }) end)
local status, err = pcall(function () a = 'a' + 1 end)
print(err)
--]]

function foo(str)
	if type(str) ~= "string" then
		error("string expected", 2)
	end
end
foo({ x = 1 })
