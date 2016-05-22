declare @currentDate datetime;
declare @output varchar(50);
set @currentDate = GetDate();
exec @output = q6 @currentDate;
print(@output);