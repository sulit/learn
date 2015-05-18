#!/usr/bin/lua

local teststr = "  I'm a worker!  "
print(teststr)

teststr = teststr:gsub("^%s*(.-)%s*$","%1")

print(teststr)
