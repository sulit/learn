#!/usr/bin/lua

function foo0 ()
end
function foo1 ()
return 'a'
end
function foo2 ()
return 'a','b'
end

x, y = foo2()
print(x,y)
x = foo2()
print(x)
x, y, z = 10, foo2()
print(x, y, z)

x, y = foo0()
print(x,y)
x, y = foo1()
print(x,y)
x, y, z = foo2()
print(x, y, z)

x,y = foo2(), 20
print(x,y)
x,y = foo0(), 20, 30
print(x,y)

print(foo0())
print(foo1())
print(foo2())
print(foo2(), 1)
print(foo2() .. "x")
print("\n")

a = {foo0()}
for i,v in ipairs(a) do
	print(v)
end
print(unpack(a))
a = {foo1()}
for i,v in ipairs(a) do
	print(v)
end
print(unpack(a))
a = {foo2()}
for i,v in ipairs(a) do
	print(v)
end
print(unpack(a))

a = {foo0(), foo2(), 4}
for k,v in pairs(a) do
	print(v)
end
print(unpack(a))
