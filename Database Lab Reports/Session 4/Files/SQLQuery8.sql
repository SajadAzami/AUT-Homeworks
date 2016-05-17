declare @output1 int;
declare @output2 int;
exec swap 123, 24, @output1 output, @output2 output ;
print(@output1);
print(@output2);