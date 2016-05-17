create function q4(@name varchar(50))
	returns int
	as
		begin
			declare @grade real;
			set @grade = (select stuGrade from tblstudent where stuName = @name);
			return @grade;
		end