#!/usr/bin/lua

-- debug.lua
gvar1 = 100
function foo()
	local var2 = 10
		function bar()
			debug.debug()
		return var2
	end
	bar()
end

debug.debug()
foo()
