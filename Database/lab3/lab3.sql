--3_1
--1:
SELECT DEPTADDR FROM DEPT WHERE DEPTNAME = 'SALES'

--2: Выдать информацию об отделах, расположенных в Chicago и New York.
SELECT * FROM DEPT WHERE lower(DEPTADDR) IN ('new york','chicago')

--3: Найти минимальную заработную плату, начисленную в 2009 году.
SELECT min(SALVALUE) FROM SALARY WHERE YEAR=2009

--4: Выдать информацию обо всех работниках, родившихся не позднее 1 января 1960 года.
SELECT * FROM EMP WHERE BIRTHDATE >= to_date('1-01-1960', 'dd-mm-yyyy')

--5: Подсчитать число работников, сведения о которых имеются в базе данных 
SELECT count(*) FROM EMP

--6: Найти работников, чьё имя состоит из одного слова. Имена выдать на нижнем регистре, с удалением стоящей справа буквы t.
SELECT CASE WHEN substr(lower(empname),-1) = 't'  THEN
                substr(lower(empname),0, length(lower(empname))-1)
ELSE 
      lower(EMPNAME)
END as name
FROM EMP WHERE EMPNAME NOT LIKE '% %'

--7: Выдать информацию о работниках, указав дату рождения в формате день(число), месяц(название), год(название). 
SELECT TO_CHAR(BIRTHDATE, 'DD-MONTH-YEAR') AS BIRTH_DATE FROM EMP;

--7: 33
SELECT TO_CHAR(BIRTHDATE, 'DD-MONTH-YYYY') AS BIRTH_DATE FROM EMP;

--8: Выдать информацию о должностях, изменив названия должности “CLERK” и “DRIVER” на “WORKER”.
SELECT (CASE jobname 
	WHEN 'DRIVER' THEN 'WORKER'
	WHEN 'DRIVER' THEN 'CLERK'
ELSE 
      jobname 
END) AS jobnam
FROM JOB;

--9: Определите среднюю зарплату за годы, в которые были начисления не менее чем за три месяца.
SELECT YEAR, AVG(SALVALUE) FROM SALARY GROUP BY YEAR HAVING COUNT(MONTH) >= 3

--10: Выведете ведомость получения зарплаты с указанием имен служащих.
SELECT e.EMPNAME, s.MONTH, s.SALVALUE FROM SALARY s NATURAL JOIN EMP e;

--11: Укажите  сведения о начислении сотрудникам зарплаты, попадающей в вилку: минимальный оклад по должности - минимальный оклад по должности плюс пятьсот. Укажите соответствующую вилке  должность.
SELECT e.EMPNAME, j.JOBNAME, s.SALVALUE, j.MINSALARY 
FROM EMP e 
NATURAL JOIN CAREER c
NATURAL JOIN JOB j
INNER JOIN SALARY s
ON s.SALVALUE BETWEEN j.MINSALARY AND j.MINSALARY + 500;

--12: Укажите сведения о заработной плате, совпадающей с минимальными окладами по должностям (с указанием этих должностей).
SELECT e.empname, s.salvalue, j.minsalary, j.jobname 
FROM salary s
INNER JOIN job j ON  s.salvalue = j.minsalary
NATURAL JOIN EMP e

--13: Найдите  сведения о карьере сотрудников с указанием вместо номера сотрудника его имени.
SELECT e.empname,  c.startdate, c.enddate FROM emp e NATURAL JOIN career c

--14: Найдите  сведения о карьере сотрудников с указанием вместо номера сотрудника его имени.
SELECT e.empname, c.startdate, c.enddate FROM emp e INNER JOIN career c USING(empno);

--15:  Выдайте сведения о карьере сотрудников с указанием их имён, наименования должности, и названия отдела.
SELECT e.empname, j.minsalary, j.jobname, d.deptname
FROM EMP e
NATURAL JOIN career c
NATURAL JOIN job j
NATURAL JOIN dept d

--16: Выдайте сведения о карьере сотрудников с указанием их имён. Выдайте сведения о карьере сотрудников с указанием их имён. Какой вид внешнего объединения Вы использовали? Составьте запрос с использованием противоположного вида соединения. Составьте запрос с использованием полного внешнего соединения.

SELECT e.empname, c.startdate, c.enddate
FROM emp e 
RIGHT JOIN career c USING(empno)
		 
SELECT e.empname, c.startdate, c.enddate
FROM emp e 
LEFT JOIN career c USING(empno)

SELECT e.empname, c.startdate, c.enddate
FROM emp e 
FULL JOIN career c USING(empno)






--3_1
--1: Найти имена сотрудников, получивших за годы начисления зарплаты минимальную зарплату.
SELECT e.empname
FROM EMP e
NATURAL JOIN JOB j
WHERE  j.minsalary =
	(SELECT min(s.salvalue) 
	FROM SALARY s 
	WHERE e.empno = s.empno)
--2: Найти имена сотрудников, работавших или работающих в тех же отделах, в которых работал или работает сотрудник с именем RICHARD MARTIN.
SELECT e.empname 
FROM EMP e
NATURAL JOIN CAREER c
WHERE c.deptno in (SELECT c.deptno 
			FROM CAREER c 
			NATURAL JOIN EMP e where e.empname = 'RICHARD MARTIN')
AND e.empname != 'RICHARD MARTIN'
GROUP BY e.empname;

--3: Найти имена сотрудников, работавших или работающих в тех же отделах и должностях, что и сотрудник 'RICHARD MARTIN'.
SELECT e.empname 
FROM EMP e
NATURAL JOIN CAREER c
WHERE (c.deptno, c.jobno) in (SELECT c.deptno, c.jobno 
					FROM CAREER c 
					NATURAL JOIN EMP e WHERE e.empname = 'RICHARD MARTIN')
AND e.empname != 'RICHARD MARTIN'
GROUP BY e.empname;

--4: Найти сведения о номерах сотрудников, получивших за какой-либо месяц зарплату большую, чем средняя зарплата   за 2007 г. или большую чем средняя зарплата за 2008г.

--5: Найти сведения о номерах сотрудников, получивших зарплату за какой-либо месяц большую, чем средние зарплаты за все годы начислений.

--6: Определить годы, в которые начисленная средняя зарплата была больше средней зарплаты за все годы начислений.

--7: Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты. 

--8: Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты.

--9: Определить номера отделов, для сотрудников которых не начислялась зарплата.

--10: Вывести сведения о карьере сотрудников с указанием названий и адресов отделов вместо номеров отделов.

--11: Определить целую часть средних зарплат,  по годам начисления.

--12: Разделите сотрудников на возрастные группы: A) возраст 20-30 лет; B) 31-40 лет; C) 41-50;    D) 51-60 или возраст не определён.

--13: Перекодируйте номера отделов, добавив перед номером отдела буквы BI для номеров <=20,  буквы  LN для номеров >=30.

--14: Выдать информацию о сотрудниках из таблицы EMP, заменив отсутствие данного о дате рождения  датой '01-01-1000'.
