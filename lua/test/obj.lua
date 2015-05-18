#!/usr/bin/lua

Account = { balance = 0}
function Account.withdraw (v)
	Account.balance = Account.balance - v
end

Account.withdraw(100.00)
print(Account.balance)
