#!/usr/bin/lua

require "string"

function allwords (f)
	for l in io.lines() do
		for w in string.gfind(l, "w%+") do
			f(w)
		end
	end
end

allwords(print)
