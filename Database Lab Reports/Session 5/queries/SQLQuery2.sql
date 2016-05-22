create trigger t1 on BOOK
instead of insert as print('No change was done');