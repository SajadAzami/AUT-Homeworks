create table Book_Audit(
	ID int identity not null primary key,
	Bookname varchar(30),
	yearpublish int,
	authorbook varchar(40),
	QTY int,
	Ins_or_del int
);