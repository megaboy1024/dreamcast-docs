/*************************************************************************
	Oracle 7 Database - Table Creation Script
	ACCOUNT - STUDENT_ADMIN
	
	The following script creates the Oracle tables and views required
	for the sample Oracle program.
*************************************************************************/

/*************************************************************************
	LOG ON USING THE STUDENT_ADMIN ACCOUNT	
*************************************************************************/
CONNECT STUDENT_ADMIN/STUDENT_ADMIN@WILBUR

/*************************************************************************
	CREATE COMMON VIEWS AND FUNCTIONS
*************************************************************************/
CREATE OR REPLACE VIEW STUDENT_ADMIN.LIST_STUDENTS AS
SELECT SSN,	FNAME||' '||LNAME AS NAME,
	DECODE(GENDER,
		'M', 'Male',
		'F', 'Female',
		'Unknown') AS GENDER,
	TO_CHAR(BIRTH_DATE,'FM MONTH DD, YYYY') AS BIRTH_DATE,
	MAJOR, DECODE (DEGREE_PROGRAM,
			'U', 'Undergraduate',
			'M', 'Masters',
			'P', 'PhD.',
			'Unknown') AS DEGREE_PROGRAM,
	NVL(TUITION_PAID,0) AS TUITION_PAID,
	NVL(TUITION_TOTAL,0) AS TUITION_TOTAL,
	NVL(TUITION_TOTAL,0) - NVL(TUITION_PAID,0) AS AMOUNT_OWED,
	NVL(LOAN_AMOUNT,0) AS LOAN_AMOUNT,
	TO_CHAR(START_DATE, 'FM MONTH DD, YYYY') AS START_DATE,
	TO_CHAR(GRAD_DATE, 'FM MONTH DD, YYYY') AS GRAD_DATE,
	NVL(TRUNC(MONTHS_BETWEEN(GRAD_DATE, BIRTH_DATE)/12),0) AS AGE_AT_GRADUATION
FROM STUDENT_ADMIN.STUDENT
/

GRANT SELECT ON STUDENT_ADMIN.LIST_STUDENTS TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM LIST_STUDENTS
/

CREATE PUBLIC SYNONYM LIST_STUDENTS FOR STUDENT_ADMIN.LIST_STUDENTS
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.LIST_ENROLLMENTS AS
SELECT S.SSN AS SSN, FNAME||' '||LNAME AS NAME,
	NVL(G.CCODE,'****') AS CCODE,
	NVL(C.CNAME,'****') AS CNAME, NVL(GRADE,'**') AS GRADE
FROM STUDENT_ADMIN.STUDENT S, DEPT_ADMIN.CLASS C, STUDENT_ADMIN.GRADE G
	WHERE S.SSN = G.SSN(+) AND G.CCODE = C.CCODE(+)
/

GRANT SELECT ON STUDENT_ADMIN.LIST_ENROLLMENTS TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM LIST_ENROLLMENTS
/

CREATE PUBLIC SYNONYM LIST_ENROLLMENTS FOR STUDENT_ADMIN.LIST_ENROLLMENTS
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.LIST_CLASSES AS
SELECT NVL(CCODE,'****') AS CCODE,
	NVL(CNAME,'****') AS CNAME,
	D.DEPT AS DEPT,
	NVL(ROOM,'****') AS ROOM,
	NVL(PREREQ,'****') AS PREREQ,
	NVL(D.DNAME,'****') AS DNAME
FROM DEPT_ADMIN.DEPT D, DEPT_ADMIN.CLASS C
	WHERE D.DEPT = C.DEPT(+)
/

GRANT SELECT ON STUDENT_ADMIN.LIST_CLASSES TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM LIST_CLASSES
/

CREATE PUBLIC SYNONYM LIST_CLASSES FOR STUDENT_ADMIN.LIST_CLASSES
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.LIST_GPA AS
SELECT S.SSN SSN, S.FNAME||' '||LNAME AS NAME,
	NVL(GPA,0) AS GPA
FROM STUDENT_ADMIN.STUDENT_GPA G, STUDENT_ADMIN.STUDENT S
	WHERE S.SSN = G.SSN(+)
/

GRANT SELECT ON STUDENT_ADMIN.LIST_GPA TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM LIST_GPA
/

CREATE PUBLIC SYNONYM LIST_GPA FOR STUDENT_ADMIN.LIST_GPA
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.LIST_STUDENT_BY_CLASS AS
SELECT NVL(C.CCODE,'****') AS CCODE, NVL(CNAME,'****') AS CNAME,
	C.DEPT AS DEPT, NVL(ROOM,'****') AS ROOM, NVL(PREREQ,'****') AS PREREQ,
	NVL(D.DNAME,'****') AS DNAME, NVL(G.SSN,'*********') AS SSN,
	NVL(G.GRADE,'**') AS GRADE
FROM DEPT_ADMIN.DEPT D, DEPT_ADMIN.CLASS C, STUDENT_ADMIN.GRADE G
	WHERE D.DEPT = C.DEPT AND C.CCODE = G.CCODE(+)
/

GRANT SELECT ON STUDENT_ADMIN.LIST_STUDENT_BY_CLASS TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM LIST_STUDENT_BY_CLASS
/

CREATE PUBLIC SYNONYM LIST_STUDENT_BY_CLASS FOR STUDENT_ADMIN.LIST_STUDENT_BY_CLASS
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.RELUCTANT_STUDENTS AS
SELECT SSN, FNAME||' '||LNAME||', social security number '||SSN||
	' is not enrolled in any classes!' AS RELUCTANT_STUDENT
FROM STUDENT_ADMIN.STUDENT WHERE NOT EXISTS
	(SELECT 'X' FROM STUDENT_ADMIN.GRADE WHERE GRADE.SSN = STUDENT.SSN)
/

GRANT SELECT ON STUDENT_ADMIN.RELUCTANT_STUDENTS TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM RELUCTANT_STUDENTS
/

CREATE PUBLIC SYNONYM RELUCTANT_STUDENTS FOR STUDENT_ADMIN.RELUCTANT_STUDENTS
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.NEEDED_CLASSES AS
SELECT SSN, FNAME||' '||LNAME AS NAME, MAJOR,
	CCODE, CNAME, DEPT, NVL(ROOM,'******') AS ROOM,
	NVL(PREREQ,'****') AS PREREQ
FROM STUDENT_ADMIN.STUDENT S1, DEPT_ADMIN.CLASS C WHERE NOT EXISTS
	(select 'X' from student_admin.student s2, student_admin.grade g
	where s2.ssn = g.ssn and s2.ssn = s1.ssn
	and g.ccode = c.ccode) AND DEPT = MAJOR
/

GRANT SELECT ON STUDENT_ADMIN.NEEDED_CLASSES TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM NEEDED_CLASSES
/

CREATE PUBLIC SYNONYM NEEDED_CLASSES FOR STUDENT_ADMIN.NEEDED_CLASSES
/

CREATE OR REPLACE VIEW STUDENT_ADMIN.EMPTY_CLASSES AS
SELECT C.CCODE, C.CNAME, C.DEPT,
	NVL(C.ROOM,'******') ROOM, NVL(C.PREREQ,'****') PREREQ
	FROM DEPT_ADMIN.CLASS C WHERE NOT EXISTS
	(SELECT 'X' FROM STUDENT_ADMIN.GRADE G WHERE G.CCODE = C.CCODE)
/

GRANT SELECT ON STUDENT_ADMIN.EMPTY_CLASSES TO DATA_ADMIN, USER_LOGON
/

DROP PUBLIC SYNONYM EMPTY_CLASSES
/

CREATE PUBLIC SYNONYM EMPTY_CLASSES FOR STUDENT_ADMIN.EMPTY_CLASSES
/

CREATE OR REPLACE FUNCTION STUDENT_ADMIN.INSERT_STUDENT
	(VSSN IN VARCHAR2, VFNAME IN VARCHAR2, VLNAME IN VARCHAR2, VGENDER IN VARCHAR2,
		VMAJOR IN VARCHAR2, VBIRTH_DATE IN VARCHAR2, VTUITION_PAID IN VARCHAR2,
	 	VTUITION_TOTAL IN VARCHAR2, VSTART_DATE IN VARCHAR2, VGRAD_DATE IN VARCHAR2,
		VLOAN_AMOUNT IN VARCHAR2, VDEGREE_PROGRAM IN VARCHAR2) RETURN NUMBER AS
BEGIN
	INSERT INTO STUDENT_ADMIN.STUDENT (SSN,FNAME,LNAME,GENDER,MAJOR,BIRTH_DATE,
	TUITION_PAID,TUITION_TOTAL,START_DATE,GRAD_DATE,LOAN_AMOUNT,DEGREE_PROGRAM)
	VALUES (VSSN, VFNAME, VLNAME, VGENDER, VMAJOR, TO_DATE(VBIRTH_DATE,'MM/DD/YYYY'),
	TO_NUMBER(VTUITION_PAID), TO_NUMBER(VTUITION_TOTAL), TO_DATE(VSTART_DATE,'MM/DD/YYYY'),
	TO_DATE(VGRAD_DATE,'MM/DD/YYYY'), TO_NUMBER(VLOAN_AMOUNT), VDEGREE_PROGRAM);
		RETURN(SQL%ROWCOUNT);
	EXCEPTION
		WHEN OTHERS THEN
			RAISE_APPLICATION_ERROR(-20001,SQLERRM);
	END INSERT_STUDENT;
/

GRANT EXECUTE ON STUDENT_ADMIN.INSERT_STUDENT TO DATA_ADMIN
/

DROP PUBLIC SYNONYM INSERT_STUDENT
/

CREATE PUBLIC SYNONYM INSERT_STUDENT FOR STUDENT_ADMIN.INSERT_STUDENT
/