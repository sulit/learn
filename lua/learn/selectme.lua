#!/usr/bin/lua

--local _, x = string.find(s, p)

function select (n, ...)
	return arg[n]
end


print(string.find("hello hello", " hel"))
print(select(1, string.find("hello hello", " hel")))
print(select(2, string.find("hello hello", " hel")))
