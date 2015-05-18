#!/usr/bin/lua
--my print

--[[
printResult = ""

function myprint(...)
	print(unpack(arg))
	for i,v in ipairs(arg) do
		printResult = printResult .. tostring(v) .. "\t"
	end
	printResult = printResult .. "\n"
	return printResult
end

print(type(myprint(1, 3, ...)))
--]]
printResult = ""

function myprint(...)
	print(unpack(arg))
end

myprint(1,2)
