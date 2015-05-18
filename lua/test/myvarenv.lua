#!/usr/bin/lua

mytb={}
local tb={["hello"] = "world"}
mytb.testtb = tb
mytb.testtb["what"] = "hi"
for k,v in pairs(tb) do
	print(k,v)
end
