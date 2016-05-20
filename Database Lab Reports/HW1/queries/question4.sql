USE DBLab1;


CREATE TABLE `Patient_Log`
(
  `ID`           INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `Patient_name` VARCHAR(30)     NOT NULL,
  `Zipcode`      INT UNIQUE      NOT NULL,
  `Doctor_name`  VARCHAR(30)     NOT NULL,
  `Problem`      VARCHAR(30)     NOT NULL,
  `State`        VARCHAR(30)     NOT NULL
);

CREATE TABLE `Doctor_Log`
(
  `Doctor_name` VARCHAR(30) PRIMARY KEY                NOT NULL,
  `DEPT_name`   VARCHAR(30)                            NOT NULL,
  `Speciality`  VARCHAR(30)                            NOT NULL,
  `Salary`      INT                                    NOT NULL,
  `State`       VARCHAR(30)                            NOT NULL
);

CREATE TRIGGER logger BEFORE DELETE ON DBLab1.Patient
FOR EACH ROW
  BEGIN
    INSERT INTO Patient_Log VALUES (Id, Patient_name, Zipcode, Doctor_name, Problem, 'Deleted');
  END;

CREATE TRIGGER logger2 BEFORE DELETE ON DBLab1.Doctor
FOR EACH ROW
  BEGIN
    INSERT INTO Doctor_Log VALUES (Doctor_name, DEPT_name, Speciality, Salary, 'Deleted');
  END;


CREATE TRIGGER logger3 BEFORE INSERT ON DBLab1.Patient
FOR EACH ROW
  BEGIN
    INSERT INTO Patient_Log VALUES (Id, Patient_name, Zipcode, Doctor_name, Problem, 'Inserted');
  END;


CREATE TRIGGER logger4 BEFORE INSERT ON DBLab1.Doctor
FOR EACH ROW
  BEGIN
    INSERT INTO Doctor_Log VALUES (Doctor_name, DEPT_name, Speciality, Salary, 'Inserted');
  END;
