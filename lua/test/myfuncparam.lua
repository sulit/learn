#!/usr/bin/lua

local function returnparam(...)
	return print(...)
end

local function mycall(...)
	print(...)
	for k,v in pairs({...}) do
		if type(v) == "function" then
			v()
			print("yes, it's runned")
		end
	end
end

function mycallx(str1,...)
	return mycall(str1,returnparam,...)
end

mycallx("hello","world","sulit")
