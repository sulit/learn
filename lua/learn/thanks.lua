#!/usr/bin/lua

--file:"thanks.lua"
--desc: to print the list of the contributing guys


helpful_guys = {
	"----参与翻译----",
	"buxiu", "凤舞影天", "zhang3",
	"morler", "lambda", "sunlight",
	"\n",

	"----参与校对----",
	"凤舞影天", "doyle", "flicker",
	"花生魔人", "zhang3", "kasicass",
	"\n",
}

for _,e in ipairs(helpful_guys) do
	print(e)
end
