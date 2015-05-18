#!/usr/bin/lua

require "table"

function list_iter(t)
	local i = 0
	local n = table.getn(t)
	return function ()
		i = i + 1
		if i <= n then
			return t[i]
		end
	end
end

list = {20, 10, 30}

for v in list_iter(list) do
	print(v)
end
