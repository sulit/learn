#!/usr/bin/lua

require "socket"

--[[
host = "www.3g.org"
file = "/TR/REC-html32.html"

threads = {}

function get (host, file)
	local co = coroutine.create(function () 
		download(host, file)
	end)
end
--]]
