alter procedure q2
	@num int
	as 
		declare @count int;
		set @count = (select count(*) from tblstudent where stuGrade < 10.0);
		print(@count);		
		if @count < @num begin 
			update tblstudent set stuGrade = stuGrade + 1 where stuGrade <= 10 AND stuGrade >= 9;
			print('count is smaller than num'); 
		end
		else begin
			update tblstudent set stuGrade = stuGrade + 0.5 where stuGrade <= 10 AND stuGrade >= 9.5;
			print('count is bigger than num');
		end