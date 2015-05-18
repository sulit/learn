#!/usr/bin/lua

days = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
}

revDays = {}
for i,v in ipairs(days) do
	revDays[v] = i
end

for i,v in ipairs(days) do
	print(v)
end

for k,v in pairs(revDays) do
	print(k,v)
end
