alter procedure swap
	@num1 int,
	@num2 int,
	@out1 int output,
	@out2 int output
	as
		set @out1 = @num2;
		set @out2 = @num1;