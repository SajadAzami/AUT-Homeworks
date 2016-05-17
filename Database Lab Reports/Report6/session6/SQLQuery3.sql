select account.account_number, saving_account.interest_rate
from account, saving_account, depositor
where account.account_number = saving_account.account_number and depositor.access_date >= '1/1/2009'