#!/usr/bin/lua

local tparser = require "parser"

sourcefile = "value.htm"
template, _, err = tparser.parse(sourcefile)
print(template)
