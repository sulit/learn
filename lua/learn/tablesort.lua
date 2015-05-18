#!/usr/bin/lua

network = {
	{name = "b", IP = "5"},
	{name = "f", IP = "9"},
	{name = "g", IP = "8"},
	{name = "c", IP = "2"}
}

rvalue = {}

rvalue = table.sort(network, function (a, b) return (a.name > b.name ) end)

for i,info in ipairs(network) do
	for k,v in pairs(info) do
		print(v)
	end
end
