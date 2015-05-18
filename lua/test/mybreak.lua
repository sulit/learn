#!/usr/bin/lua

local testnums = {1,2,3,4,5,6,7,8,9,0}

for k,v in pairs(testnums) do
	if v == 5 then
		break
	end
	print(v)
end
