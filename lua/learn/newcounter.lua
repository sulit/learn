#!/usr/bin/lua

function mytest (i)
	i = i + 1
	return i
end
function newCounter2()
	local i = 0
	i = mytest(i)
	return i
end

function newCounter1()
	local i = 0
	return function ()
		i = i + 1
		return i
	end
end

c1 = newCounter1()
c2 = newCounter2()

print(c1())
print(c1())
print(c2())
print(c2())
