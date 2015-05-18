#!/usr/bin/lua

--[=[
local chunk = [==[
username=root&password=127028
------WebKitFormBoundary0mT4NYdD1R8EAnB5
Content-Disposition: form-data; name=cbi.submit

1
------WebKitFormBoundary0mT4NYdD1R8EAnB5
Content-Disposition: form-data; name=cbid.password.1.pw1

127028
------WebKitFormBoundary0mT4NYdD1R8EAnB5
Content-Disposition: form-data; name=cbid.password.1.pw2

127028
------WebKitFormBoundary0mT4NYdD1R8EAnB5--

username=root&password=127028
username=root&password=127028
]==]
local field={headers={}}
repeat
	chunk, stat = chunk:gsub("^([A-Z][A-Za-z0-9%_]+): +([^\r\n]+\r\n)", function(k, v) field.headers[k]=v return "" end)
until stat == 0
--[[
for k,v in pairs(field.headers) do
	print(k, v)
end
]]
--chunk, stat=chunk:gsub("^\r\n","")
chunk, stat=chunk:gsub("^\r\n","")
if stat then
	print(chunk)
end
--]=]

local teststr = [[
hello

world
]]

teststr = string.gsub(teststr, "^\n", "")
print(teststr)
