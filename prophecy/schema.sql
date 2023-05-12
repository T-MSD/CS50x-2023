CREATE TABLE students (
    student_name TEXT,
    PRIMARY KEY(student_name)
);

CREATE TABLE houses (
    house TEXT,
    student TEXT,
    FOREIGN KEY(student) REFERENCES students(student_name)
);

CREATE TABLE assignments (
    assignment TEXT,
    student TEXT,
    FOREIGN KEY(student) REFERENCES students(student_name)
);

/* https://cs50.readthedocs.io/libraries/cs50/python/ */
/* https://stackoverflow.com/questions/5208245/what-is-causing-foreign-key-mismatch-error */
