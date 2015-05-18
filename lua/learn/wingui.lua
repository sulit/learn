#!/usr/bin/lua

w = Window {
	x = 0,
	y = 0,
	width = 300,
	height = 200,
	title = "Lua",
	background = "blue",
	border = true
}

function Window (options)
{
	if type(options.title) ~= "string" then
		error("no title")
	elseif type(options.width) ~= "number" then
		error("no width")
	elseif type(options.height ~= "number") then
		error("no height")
	end
}
