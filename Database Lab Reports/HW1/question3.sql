CREATE FUNCTION q3(patient_id INT)
  RETURNS VARCHAR(10)
DETERMINISTIC
  BEGIN
    DECLARE spec VARCHAR(30);

    SET spec = (SELECT Speciality
                FROM Doctor
                  NATURAL JOIN Patient
                WHERE ID = patient_id);
    RETURN (spec);
  END
