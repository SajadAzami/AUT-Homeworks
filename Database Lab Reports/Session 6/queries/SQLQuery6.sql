declare @output1 int;
declare @output2 int;
exec p6_3 'cname1' , @output1 output, @output2 output
print(@output1);
print(@output2);