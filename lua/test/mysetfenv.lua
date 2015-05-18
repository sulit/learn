#!/usr/bin/lua

local func=require("a")
local mytest=func.test
local FuncEnv = setmetatable({}, {__index = _G})
setfenv(mytest,FuncEnv)--等价于setenv(func,FuncEnv);func();
mytest()--FuncEnv就是新的模块啦，可以用其中的函数啦,其实，lua内部的model命令或者函数也是用的这个原理
