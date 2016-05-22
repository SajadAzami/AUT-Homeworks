create procedure p6_5
	@customer_id int
	as
		select * from customer
		where customer.customer_id = @customer_id