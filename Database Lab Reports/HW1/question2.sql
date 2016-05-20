USE DBLab1;
CREATE PROCEDURE q1(IN id INT, name VARCHAR(30))
  BEGIN
    DECLARE flag INT;
    IF exists(SELECT *
              FROM Patient
              WHERE Patient.ID = id AND Doctor_name = name)
    THEN
      SET flag = 1;
    ELSE SET flag = 0;
    END IF;
    IF flag = 1
    THEN
      SELECT
        Doctor_name,
        Speciality
      FROM Doctor
        NATURAL JOIN Patient
      WHERE Patient.ID = id AND Patient_name = @name;
    ELSE
      INSERT INTO Patient VALUES (@id, @name, 12345, 'RandomDoctor', 'RandomProblem');
    END IF;
  END
