select account.account_number, saving_account.interest_rate
from account, saving_account, depositor
where depositor.access_date > "2009" and account.account_number