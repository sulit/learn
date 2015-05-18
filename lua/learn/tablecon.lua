#!/usr/bin/lua

local t = {}
for line in io.lines() do
	table.insert(t, line)
end
s = table.concat(t, "\n") .. "\n"
print(s)

for k,v in pairs(t) do
	print(v)
end

for i,v in ipairs(t) do
	print(v)
end
