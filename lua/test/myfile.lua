#!/usr/bin/lua

local f = io.open("./filetest.txt","a+")
for i=1,10 do
	f:write(i.."\n")
end
f:close()
