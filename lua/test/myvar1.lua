#!/usr/bin/lua

context={}

local function test1 ()
	local ctx = context
	ctx.hello = "world"
end
local function test2 ()
	print(context.hello)
end

test1()
test2()
