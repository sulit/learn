#!/usr/bin/lua

coro = {}

coro.main = function () end
coro.current = coro.main

for k,v in pairs(coro) do
	print(k, v)
end

function coro.create(f)
	return coroutine.wrap(function(val)
		return nil, f(val)
	end)
end

function coro.transfer(k,val)
	if coro.current ~= coro.main then
		return coroutine.yield(k,val)
	else
		while k do
			coro.current = k
			if k == coro.main then
				return val
			end
			k, val = k(val)
		end
		error("coroutine ended without transfering control ...")
	end
end

function foo1(n)
	print("1: foo1 received value "..n)
	n = coro.transfer(foo2,n + 10)
	print("2: foo1 received value "..n)
	n = coro.transfer(coro.main,n + 10)
	print("3: foo1 received value "..n)
	coro.transfer(coro.main,n + 10)
end

function foo2(n)
	print("1: foo2 received value "..n)
	n = coro.transfer(coro.main,n + 10)
	print("2: foo2 received value "..n)
	coro.transfer(foo1,n + 10)
end

function main()
	foo1 = coro.create(foo1) --产生协程foo1
	foo2 = coro.create(foo2) --产生协程foo2
	local n = coro.transfer(foo1,0)
	print(n)
	print("1: main received value "..n)
	n = coro.transfer(foo2,n + 10)
	print("2: main received value "..n)
	n = coro.transfer(foo1,n + 10)
	print("3: main received value "..n)
end

--把main设为主函数(协程)
coro.main = main
--将coro.main设为当前协程
coro.current = coro.main
--开始执行主函数(协程)
coro.main()

--[[
上面的示例定义了一个名为main的主函数，整个程序由它而始，也因它而终。为什么需要一个这样的主函数呢？上面说了，程序控制权可以在对称式协程之间自由地直接传递，它们之间无所谓谁从属于谁的问题，都处于同一个层级，但是应用程序必须有一个开始点，所以我们定义一个主函数，让它点燃程序运行的导火线。虽说各个协程都是平等的，但做为程序运行原动力的主函数仍然享有特殊的地位(这个世上哪有绝对的平等！)，为此我们的库专门用了一个coro.main变量来保存主函数，并且在它执行之前要将它设为当前协程(虽然上面的main实际只是一个普通函数而非一个真正的协程，但这并无太大的关系，以后主函数也被称为主协程)。示例运行的结果是：

1: foo1 received value 0
1: foo2 received value 10
1: main received value 20
2: foo2 received value 30
2: foo1 received value 40
2: main received value 50
3: foo1 received value 60
3: main received value 70

协程的执行序列是：main->foo1->foo2->main->foo2->foo1->main->foo1->main。

    coro.transfer(k,val)函数中k是将要接收程序控制权的协程，而val是传递给k的数据。如果当前协程不是主协程，tansfer(k,val)就简单地利用coroutine.yield(k,val)将当前协程挂起并传回两项数据，即程序控制权的下一站和传递给它的数据；否则进入一个控制权分派(dispatch)循环，该循环(重)启动(resume)k协程，等待它执行到挂起(suspend)，并根据此时协程传回的数据来决定下一个要(重)启动的协程。从应用示例来看，协程与协程之间似乎是用transfer直接传递控制权的，但实际上这个传递还是通过了主协程。每一个在主协程里被调用(比较coro.current和coro.main是否相同即可判断出)的transfer都相当于一个协程管理器，它不断地(重)启动一个协程，将控制权交出去，然后等那个协程挂起时又将控制权收回，然后再(重)启动下一个协程...，这个动作不会停止，除非<1>将(重)启动的协程是主协程；<2>某个协程没有提供控制权的下一个目的地。很显然，每一轮分派循环开始时都由主协程把握控制权，在循环过程中如果控制权的下一站又是主协程的话就意味着这个当初把控制权交出去的主协程transfer操作应该结束了，所以函数直接返回val从而结束这轮循环。对于情况<2>，因为coro.create(f)创建的协程的体函数(body function)实际是function(val) return nil,f(val) end，所以当函数f的最后一条指令不是transfer时，这个协程终将执行完毕并把nil和函数f的返回值一起返回。如果k是这样的协程，transfer执行完k,val = k(val)语句后k值就成了nil，这被视为一个错误，因为程序此时没法确定下一个应该(重)启动的协程到底是谁。所以在对称式模型下，每一个协程(当然主协程出外)最后都必须显式地将控制权传递给其它的协程。根据以上分析，应用示例的控制权的分派应为：

	第一轮分派: main->foo1->main->foo2->main->main(结束)
	第二轮分派: main->foo2->main->foo1->main->main(结束)
	第三轮分派: main->foo1->main->main(结束)

	    由于可以直接指定控制权传递的目标，对称式协程机制拥有极大的自由，但得到这种自由的代价却是牺牲程序结构。如果程序稍微复杂一点，那么即使是非常有经验的程序员也很难对程序流程有全面而清晰的把握。这非常类似goto语句，它能让程序跳转到任何想去的地方，但人们却很难理解充斥着goto的程序。非对称式协程具有良好的层次化结构关系，(重)启动这些协程与调用一个函数非常类似：被(重)启动的协程得到控制权开始执行，然后挂起(或结束)并将控制权返回给协程调用者，这与计算机先哲们倡导的结构化编程风格完全一致。

		    综上所述，Lua提供的非对称式协程不但具有与对称式协程一样强大的能力，而且还能避免程序员滥用机制写出结构混乱的程序。
--]]
