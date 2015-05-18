#!/usr/bin/lua

---[=[
Set = {}
local mt = {}

function Set.new(l)
	local set = {}
	setmetatable(set, mt)
	for _,v in ipairs(l) do
		set[v] = true
	end

	return set
end

function Set.union(a, b)
	local res = Set.new{}
	for k in pairs(a) do
		res[k] = true
	end
	for k in pairs(b) do
		res[k] = true
	end

	return res
end

function Set.intersection(a, b)
	local res = Set.new{}
	for k in pairs(a) do
		res[k] = b[k]
	end

	return res
end

function Set.tostring(set)
	local l = {}
	
	for e in pairs(set) do
		l[#l+1] = e
	end

	return "{" .. table.concat(l, ", ") .. "}"
end

function Set.print(s)
	print(Set.tostring(s))
end


s1 = Set.new{10, 20, 30, 50}
s2 = Set.new{30, 1}
print(getmetatable(s1))
for k,v in pairs(getmetatable(s1)) do
	print(k,v)
end
--print(getmetatable(s2))
for k,v in pairs(getmetatable(s2)) do
	print(k,v)
end
--将元方法加入元表
mt.__add = Set.union   --指定加号为求并集的方法
mt.__mul = Set.intersection  --指定乘号为交集的方法

--s1 = Set.new{11,22,31,44,56}
--s2 = Set.new{66,33,22,31}
--print(getmetatable(s1))
--print(getmetatable(s2))

s3 = s1 + s2 --求并集   
Set.print(s3) --输出 {11, 31, 66, 22, 33, 56, 44}
s4 = s1 * s2 --求交集
Set.print(s4) --输出 {31, 22}
--]=]

mt.__metatable = "not your business"

s1 = Set.new{}
print(getmetatable(s1))
setmetatable(s1,{})


--[[
Set = {}  --集合

local mt = {}  --集合元表

--根据参数列表中的值创建一个新的集合
function Set.new(l)
	local set = {}
	setmetatable(set,mt)  --指定 table set的元表为mt
	for k,v in ipairs(l) do
		set[v] = true    --注意，是拿索来当数据用的
	end

	return set
end

function Set.union(a,b)
	local res = Set.new{}
	for k,v in pairs(a) do res[k] = true end
	for k,v in pairs(b) do res[k] = true end

	return res
end

function Set.intersection(a,b)
	local res = Set.new{}
	for k,v in pairs(a) do
		if b[k] then
			res[k] = true
		end
	end
	return res
end

function Set.tostring(set)
	local l = {}
	for k,v in pairs(set) do
		l[#l + 1] = k
	end

	return "{" .. table.concat(l,", ") .. "}"
end

function Set.print(s)
	print(Set.tostring(s))
end


--将元方法加入元表
mt.__add = Set.union   --指定加号为求并集的方法
mt.__mul = Set.intersection  --指定乘号为交集的方法

s1 = Set.new{11,22,31,44,56}
s2 = Set.new{66,33,22,31}
print(getmetatable(s1))
print(getmetatable(s2))

s3 = s1 + s2 --求并集   
Set.print(s3) --输出 {11, 31, 66, 22, 33, 56, 44}
s4 = s1 * s2 --求交集
Set.print(s4) --输出 {31, 22}
--]]
