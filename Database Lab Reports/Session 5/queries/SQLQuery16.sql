create trigger prevent_drop on DATABASE 
FOR DROP_TABLE
AS
RAISERROR ('Unauthorized DROP TABLE', 10, 1);
rollback;
