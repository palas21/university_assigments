import psycopg2

def get_employees(): # this function gets all the employees from the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()
    cur.execute("SELECT employee.jobtitle, person.firstname, person.middlename, person.lastname, employee.businessentityid FROM humanresources.employee join person.person on employee.businessentityid = person.businessentityid")
    rows = cur.fetchall()
    return rows

def get_employee(id): # this function gets a specific employee from the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()
    cur.execute("""
        SELECT employee.jobtitle, person.firstname, person.middlename, person.lastname, person.businessentityid 
        FROM humanresources.employee 
        JOIN person.person ON employee.businessentityid = person.businessentityid 
        WHERE employee.businessentityid = %s
    """, (id,))
    row = cur.fetchall()
    return row

def update_employee(id, firstname, middlename, lastname, jobtitle): # this function updates an employee in the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    # we update the person table
    cur.execute(""" 
        UPDATE person.person 
        SET firstname = %s, middlename = %s, lastname = %s 
        WHERE businessentityid = %s
    """, (firstname, middlename, lastname, id))
    conn.commit()
     
    # we update the employee table
    cur.execute("""
        UPDATE humanresources.employee 
        SET jobtitle = %s 
        WHERE businessentityid = %s
    """, (jobtitle, id))
    conn.commit()

def add_employee(id, nationalidnumber, jobtitle, birthdate, maritalstatus, gender, hiredate): # this function adds an employee to the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    # we add the employee to the employee table there is also a formul for the loginid.
    cur.execute("""insert into humanresources.employee (businessentityid, nationalidnumber, 
                loginid, jobtitle,birthdate,hiredate,gender,maritalstatus) values (%s,%s,
                CONCAT(\'adventure-works\\', LOWER((SELECT firstname FROM person.person WHERE person.businessentityid = %s)), 
                (SELECT COUNT(*) FROM person.person join humanresources.employee on employee.businessentityid = person.businessentityid WHERE firstname = (SELECT firstname FROM person.person WHERE person.businessentityid = %s)))
                ,%s,%s,%s,%s,%s)""", (id,nationalidnumber,id,id,jobtitle,birthdate,hiredate,gender,maritalstatus))
    conn.commit()

def delete_employee(id): # this function deletes an employee from the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    # we delete the employee from the employeedepartmenthistory table first
    cur.execute("DELETE FROM humanresources.employeedepartmenthistory WHERE businessentityid = %s", (id,))
    conn.commit()

    # then we delete the employee from the employeepayhistory table 
    cur.execute("DELETE FROM humanresources.employeepayhistory WHERE businessentityid = %s", (id,))
    conn.commit()

    # finally we delete the employee from the employee table
    cur.execute("DELETE FROM humanresources.employee WHERE businessentityid = %s", (id,))
    conn.commit()

def search_employee_name(fullname): # this function searches for an employee by fullname
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    cur.execute("""
        SELECT employee.jobtitle, person.firstname, person.middlename, person.lastname, person.businessentityid 
        FROM humanresources.employee 
        JOIN person.person ON employee.businessentityid = person.businessentityid 
        WHERE lower(person.firstname) LIKE lower(%s) 
           OR lower(person.middlename) LIKE lower(%s) 
           OR lower(person.lastname) LIKE lower(%s)
    """, (f"%{fullname}%", f"%{fullname}%", f"%{fullname}%"))

    rows = cur.fetchall()
    return rows

def search_employee_job(jobtitle): # this function searches for an employee by jobtitle
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    cur.execute("""
        SELECT employee.jobtitle, person.firstname, person.middlename, person.lastname, person.businessentityid 
        FROM humanresources.employee 
        JOIN person.person ON employee.businessentityid = person.businessentityid 
        WHERE lower(employee.jobtitle) LIKE lower(%s)
    """, (f"%{jobtitle}%",))

    rows = cur.fetchall()
    return rows

def get_employee_info(id): # this function gets the spesific employee info from the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    cur.execute("""
        SELECT
            P.BusinessEntityID,
            P.PersonType,
            P.NameStyle,
            P.Title,
            P.FirstName,
            P.MiddleName,
            P.LastName,
            P.Suffix,
            P.EmailPromotion,
            P.AdditionalContactInfo,
            P.Demographics,
            P.rowguid AS PersonRowGuid,
            P.ModifiedDate AS PersonModifiedDate,
            E.NationalIDNumber,
            E.LoginID,
            E.JobTitle,
            E.BirthDate,
            E.MaritalStatus,
            E.Gender,
            E.HireDate,
            E.SalariedFlag,
            E.VacationHours,
            E.SickLeaveHours,
            E.CurrentFlag,
            E.rowguid AS EmployeeRowGuid,
            E.ModifiedDate AS EmployeeModifiedDate
        FROM
            person.Person AS P
        JOIN
            humanresources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
        WHERE P.BusinessEntityID = %s
    """, (id,))

    row = cur.fetchall()
    return row

def get_persons(): # this function gets all the persons from the database
    conn = psycopg2.connect(database="Adventureworks", user="postgres", password="test", host="127.0.0.1", port="5432")
    cur = conn.cursor()

    cur.execute("""
        SELECT p.businessentityid, p.firstname, p.middlename, p.lastname
        FROM person.person AS p
        LEFT JOIN humanresources.employee AS e ON p.businessentityid = e.businessentityid
        WHERE e.businessentityid IS NULL
    """)
    rows = cur.fetchall()
    
    return rows