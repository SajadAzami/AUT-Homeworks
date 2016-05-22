create trigger t2 on BOOK
after insert ,delete as 
insert into Book_Audit(ID,Bookname,yearpublish,authorbook,QTY,Ins_or_del) select * ,1 from inserted;
insert into Book_Audit(ID,Bookname,yearpublish,authorbook,QTY,Ins_or_del) select * ,0 from deleted;
