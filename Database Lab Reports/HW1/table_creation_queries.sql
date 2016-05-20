CREATE DATABASE DBLab1;

USE DBLab1;

CREATE TABLE `Patient`
(
  `ID`           INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `Patient_name` VARCHAR(30)     NOT NULL,
  `Zipcode`      INT UNIQUE      NOT NULL,
  `Doctor_name`  VARCHAR(30)     NOT NULL,
  `Problem`      VARCHAR(30)     NOT NULL,
  FOREIGN KEY (Doctor_name)
  REFERENCES Doctor (Doctor_name)
    ON UPDATE CASCADE
    ON DELETE CASCADE
);

CREATE TABLE `Doctor`
(
  `Doctor_name` VARCHAR(30) PRIMARY KEY                NOT NULL,
  `DEPT_name`   VARCHAR(30)                            NOT NULL,
  `Speciality`  VARCHAR(30)                            NOT NULL,
  `Salary`      INT                                    NOT NULL
);

ALTER TABLE Doctor
  ADD CONSTRAINT cnst1 CHECK (Salary > 5000)
