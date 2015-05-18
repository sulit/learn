local dofile, pcall, _G = dofile, pcall, _G

local name

if pcall(dofile, "./dofiletest") and _G.name then
	name = _G.name
end

if name then
	print(name)
end
