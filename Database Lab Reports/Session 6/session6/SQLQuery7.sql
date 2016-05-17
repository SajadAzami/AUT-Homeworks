create procedure p6_4
	@paymnetnumber int,
	@bname varchar(50) output
	as 
		set @bname = (select loan.branch_name from loan, payment
		where loan.loan_number = payment.loan_number and @paymentnumber = payment.payment_number)