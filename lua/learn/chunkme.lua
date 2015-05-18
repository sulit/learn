#!/usr/bin/lua

--[[
local math = require "math"
local a , b, c = 1, 2, 3

do
	local a2 = 2*a
	local d = math.sqrt(b^2 - 4*a*c)
	x1 = (-b + d)/a2
	x2 = (-b - d)/a2
end 

print(x1, x2)
--]]

for i=1,10 do
	print(i)
end
max = i
print(max)
