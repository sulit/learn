#!/usr/bin/lua

require "http"
require "util"

hello = util.hello

hello.why = "nowhy"
for k,v in pairs(hello) do
	print(k,v)
end

http.hello.why="what"

for k,v in pairs(http.hello) do
	print(k,v)
end
