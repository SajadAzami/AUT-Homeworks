create function test(@input int)
	returns int
	as 
		begin
			insert into tlbpostalcode values ('Akbar', 'Mahmoodi', 12345);
			return 0;
		end