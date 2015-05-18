#!/usr/bin/lua

x = 10
local i = 1

while i<=x do
	local x = i*2
	print(x)
	i = i + 1
end 

print("Now i is  "..i)
print("Now x is  "..x)

if i > 20 then
	local x
	x = 20
	print(x + 2)
else
	print(x)
end

print("Now x is  "..x)
