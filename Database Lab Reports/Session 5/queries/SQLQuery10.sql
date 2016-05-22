create trigger t3 on BOOK
after update as if update(bookname) rollback;