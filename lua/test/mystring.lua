#!/usr/bin/lua5.1

local c = "name=sulit"
local p = "name=".."(.-)"
print(p)
local i,j,v = c:find(p)
print(i, j, v)

