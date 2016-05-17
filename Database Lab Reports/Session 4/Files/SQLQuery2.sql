create procedure q10
	as 
		declare @count int;
		set @count = (select count(*) from tblstudent where stuGrade < 10.0);
		print(@count);		
		if @count < 2
			print('Good');	
		else if @count > 3
			print('Bad');
		else
			print('Normal');