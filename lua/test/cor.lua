#!/usr/bin/lua

local co = coroutine.create(
	function (...)
		print("hello")
		coroutine.yield()
		print(...)
	end
)
if co then
	print(co)
end
coroutine.resume(co,1)
coroutine.resume(co,2)
if coroutine.status(co) ~= "dead" then
	coroutine.resume(co,8)
end
