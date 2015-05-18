#!/usr/bin/lua

function urldecode( str, no_plus )
--str = "", no_plus = true

	local function __chrdec( hex )
		return string.char( tonumber( hex, 16 ) )
	end

	if type(str) == "string" then
		if not no_plus then
			str = str:gsub( "+", " " )
		end

		str = str:gsub( "%%([a-fA-F0-9][a-fA-F0-9])", __chrdec )
	end

	print(str)
end

local str = ""
urldecode(str, true)
