create view q6_2 as
select customer.customer_id, customer.customer_name, loan.amount, branch.branch_name
from customer, branch, loan, borrower
where customer.customer_id = borrower.customer_id and borrower.loan_number = loan.loan_number 
and loan.branch_name = branch.branch_name