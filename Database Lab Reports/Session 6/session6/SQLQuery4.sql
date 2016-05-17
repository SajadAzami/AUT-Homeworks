select payment.payment_number
from payment, loan, branch
where payment.loan_number = loan.loan_number and branch.branch_name = loan.branch_name
and branch.branch_city = 'tehran'