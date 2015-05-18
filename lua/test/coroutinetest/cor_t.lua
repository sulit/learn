#!/usr/bin/lua

--[[
co = coroutine.create(function (a, b, c) 
		print("co", a, b, c)
	end)

coroutine.resume(co, 1, 2, 3)
--]]

--[[
co = coroutine.create(function (a, b) 
		print(a + b, a - b)
	end)

coroutine.resume(co, 20, 10)
--]]

---[[
function receive ()
	local status, value = coroutine.resume(producer)
	return value
end

function send(x)
	coroutine.yield(x)
end

producer = coroutine.create(
	function ()
		while true do
			local x = io.read()
			send(x)
		end
end)

print(receive())
print(receive())
print(coroutine.status(producer))
--]]
