create function f6_1()
	returns int
	as 
		begin
			declare @id int;
			declare @max int;
			select @max = max(interest_rate) from saving_account;
			set @id = (select account_number from saving_account where @max = saving_account.interest_rate)
			return @id
		end