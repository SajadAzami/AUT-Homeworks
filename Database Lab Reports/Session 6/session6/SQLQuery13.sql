create function f6_2(@id int)
	returns varchar(50)
	as 
		begin
			declare @deptname varchar(50);
			set @deptname = (select dependent_name from employee where employee.employee_id = @id)
			return @deptname
		end