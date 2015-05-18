#!/usr/bin/lua

---[[
local t = {}
print(getmetatable(t))

local t1 = {}
print(t1)
setmetatable(t,t1)
assert(getmetatable(t)==t1)
print(getmetatable(t))
--]]
--[[
local function _instantiate(class, ...)
	local inst = setmetatable({}, {__index = class})

	if inst.__init__ then
		inst:__init__(...)
	end

	return inst
end

function class(base)
	return setmetatable({}, {
		__call  = _instantiate,
		__index = base
	})
end

mytest = class("test")
function mytest.__init__(self,title)
	self.text = title
	print(self.text)
end
mytest("hello")
--]]
