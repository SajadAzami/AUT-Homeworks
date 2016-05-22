create procedure p6_3
	@name varchar(50),
	@balance int output,
	@account_number int output
	as 
		set @balance = (select account.balance from account, depositor, customer
		where account.account_number = depositor.account_number and customer.customer_name = @name 
		and customer.customer_id = depositor.customer_id)
		set @account_number = (select account.account_number from account, depositor, customer
		where account.account_number = depositor.account_number and customer.customer_name = @name 
		and customer.customer_id = depositor.customer_id)
	