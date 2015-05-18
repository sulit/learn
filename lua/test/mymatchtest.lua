#!/usr/bin/lua

local str = "set client"

local str1, str2 = str:match("^(%S+) (%S+)$")
print(str1, str2)

local str3, str4 = (nil or str:match("^(%S+) (%S+)$"))
print(str3, str4)
