#!/usr/bin/lua

--[[
a = {
	x = 0,
	y = 0,
}

print(a.x)
print(a["x"])
--]]

list = nil

for line in io.lines() do
	list = {next = list, value = line}
end

l = list

while l do
	print(l.value)
	l = l.next
end
