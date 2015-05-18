#!/usr/bin/lua

argv={"echo","$what"}
for k,v in pairs(argv) do
	print(k,v)
end

for i, v in ipairs(argv) do
	if v:match("[^%w%.%-i/]") then
		argv[i] = '"%s"' % v:gsub('"', '\\"')
	end 
end 

for k,v in pairs(argv) do
	print(k,v)
end
