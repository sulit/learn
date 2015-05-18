#!/usr/bin/lua

local function _instantiate(class, ...)
	local inst = setmetatable({}, {
		__index = class
	})

	if inst.__init__ then
		inst:__init__(...)
	end

	return inst
end

function class(base)
	return setmetatable({},{
		__call=_instantiate,
		__index=base
	})
end

Node = class() --Node是个table
--print(Node)
function Node.__init__ (self, title, description)
	self.title = title
	self.description = description
end

local nodevalue = Node("hello","world")
for k,v in pairs(nodevalue) do
	print(k,v)
end
