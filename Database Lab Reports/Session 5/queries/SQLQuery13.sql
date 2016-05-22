create trigger t10 on v10
instead of insert as begin
declare @temp int;
set @temp = (select QTY from inserted);
if @temp < 1000
		begin
			insert into v10 (Bookname, authorbook, QTY)
			select Bookname , authorbook ,1000
			from inserted
		end
	else begin
		insert into v10 (Bookname, authorbook, QTY)
		select Bookname , authorbook ,QTY
		from inserted
	end
end