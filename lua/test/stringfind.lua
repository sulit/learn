#!/usr/bin/lua

local teststr = "hello"

--[[
local deststr = nil
deststr = teststr:match("(world)") or teststr:match("(hel%S+)")
print(deststr)
--]]

--local uptime = io.open("uptime.txt")
local uptime = io.open("uptime.txt")
--local uptime = io.popen("uptime")

--[[
local uptimestr = uptime:read("*a")
uptime:close()
--]]
for uptimestr in uptime:lines() do
local day,hour,min = uptimestr:match("(%d+)%s+days,%s+(%d+):(%d+),") or nil,uptimestr:match("(%d+):(%d+),")
if not hour then
	day,min = uptimestr:match("(%d+)%s+days,%s+(%d+)%s+min,") or nil,uptimestr:match("(%d+)%s+min,")
end
print(day,hour,min)
end

