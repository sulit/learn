#!/usr/bin/lua

a = {}
setmetatable(a,b)
key = {}
print(key)
a[key] = 1
key = {}
print(key)
a[key] = 2
collectgarbage()
for k,v in pairs(a) do
	print(v)
end
