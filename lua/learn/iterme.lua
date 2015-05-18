#!/usr/bin/lua

function iter (a, i)
	i = i + 1
	local v = a[i]
	if v then
		return i, v
	end
end

function myipairs (a)
	print(iter, a, 0)
	return iter, a, 0
end

a = {"one", "two", "three"}
for i, v in myipairs(a) do
	print(i, v)
end
