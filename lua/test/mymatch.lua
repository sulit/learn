#!/usr/bin/lua

--[[
function printvar(passwd, loc, rem)
	if passwd then
		print(passwd)
	end
	if loc then
		print(loc)
	end
	if rem then
		print(rem)
	end
end

local teststr="set client tunnel passwd pwd local loc remote rem"
local passwd, loc, rem = teststr:match("^set client tunnel passwd (%S+)$") or teststr:match("^set client tunnel passwd (%S+) local (%S+)()$") or teststr:match("^set client tunnel passwd (%S+) ()remote (%S+)$") or teststr:match("^set client tunnel passwd (%S+) local (%S+) remote (%S+)$")
print("all")
printvar(passwd, loc, rem)
passwd, loc, rem =teststr:match("^set client tunnel passwd (%S+) local (%S+) remote (%S+)$")
print("long")
printvar(passwd, loc, rem)
passwd, loc, rem =teststr:match("^set client tunnel passwd (%S+)$")
print("short")
printvar(passwd, loc, rem)
passwd, loc, rem =teststr:match("^set client tunnel passwd (%S+) local (%S+)()$")
print("midlocal")
printvar(passwd, loc, rem)
passwd, loc, rem =teststr:match("^set client tunnel passwd (%S+) ()remote (%S+)$")
print("midremote")
printvar(passwd, loc, rem)
--]]

--[[
local str = "set hello"
local str1, str2 = nil or str:match("^(%S+) (%S+)$") --这里str1会有值，str2会是nil，原因是or是或运算，运算结果只有一个值
print(str1, str2)
if str1 then
	print(str1)
end

if str2 then
	print(str2)
end
--]]

local hello = "hello world"

local str1, str2, str3 = hello:match("^(%S+) ()(%S+)$")
print(str1, str2, str3) --str2为第二个括号所在的字符位置数,此处为7
--world=worldl
