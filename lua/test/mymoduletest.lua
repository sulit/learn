#!/usr/bin/lua

--local mymodule = require "mymodule"

local loader = package.loaders[2]
local mymodule = loader("mymodule")

if type(mymodule) == "function" then
	print("yes,it's loader")
end

--print(loader)
mymodule()
print("world")
