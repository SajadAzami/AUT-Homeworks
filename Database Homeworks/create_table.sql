CREATE TABLE Patient (
  Problem      VARCHAR(40),
  Doctor_name  VARCHAR(30),
  Zip_code     INT UNIQUE,
  Patient_name VARCHAR(30),
  ID           INT AUTO_INCREMENT PRIMARY KEY,
  FOREIGN KEY (Doctor_name) REFERENCES Doctor (Doctor_name)
);

CREATE TABLE Doctor (
  Salary      INT,
  Specialty   VARCHAR(30),
  DEPT_name   VARCHAR(30) UNIQUE,
  Doctor_name VARCHAR(30) PRIMARY KEY
)