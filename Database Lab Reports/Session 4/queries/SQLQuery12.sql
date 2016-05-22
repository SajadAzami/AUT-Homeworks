select FirstName, LastName, PostalCode,
		 ROW_NUMBER() over (order by PostalCode) as	rowNumber,
		 RANK() over (order by PostalCode) as	rankNumber,
		 DENSE_RANK() over (order by PostalCode) as	denseRank
		from tblpostalcode