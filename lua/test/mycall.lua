#!/usr/bin/lua

--[[
function f(tb,x,y) return x+y+tb.n end
b={}
b.__call = f
a = {}
	a.n=100
	setmetatable(a,b)
	print(a(1,2))
	print(a(1))
print(a.n)
	--]]


a = {}
function a:Func()
	print("simonw")
end
c = {}
local function ccall(t,...)
	print("Start")
	print(...)
	t.Func()
	print("End")
end
c.__call = ccall
--[[
c.__call = function(t, ...)
	print("Start")
	t.Func()
	print("End")
	end
--]]
	setmetatable(a, c)
a("hello","world")
	--[[
	Start
	simonw
	End
	]]
