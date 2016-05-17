alter function q6(@currentDate datetime)
	returns varchar(50)
	as
	begin
		declare @temp datetime;
		set @temp = (dateAdd(day,4,@currentDate));
		return datename(day,@temp);
	end