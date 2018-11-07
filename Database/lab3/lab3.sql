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
SELECT 
CASE WHEN substr(lower(empname),-1) = 't' 
	THEN substr(lower(empname),0, length(lower(empname))-1)
ELSE 
    lower(EMPNAME)
END as name
FROM EMP WHERE EMPNAME NOT LIKE '% %'

--7: Выдать информацию о работниках, указав дату рождения в формате день(число), месяц(название), год(название). 
SELECT TO_CHAR(BIRTHDATE, 'DD-MONTH-YEAR', 'nls_date_language=russian') AS BIRTH_DATE FROM EMP;

--7: 33
SELECT TO_CHAR(BIRTHDATE, 'DD-MONTH-YYYY') AS BIRTH_DATE FROM EMP;

--8: Выдать информацию о должностях, изменив названия должности “CLERK” и “DRIVER” на “WORKER”.
SELECT (CASE jobname 
	WHEN 'DRIVER' THEN 'WORKER'
	WHEN 'CLERK' THEN '“WORKER”'
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
NATURAL JOIN SALARY s
WHERE  s.SALVALUE=
	(SELECT min(s.salvalue) 
	FROM SALARY s)

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
AND e.empname != 'RICHARD MARTIN';

--4: Найти сведения о номерах сотрудников, получивших за какой-либо месяц зарплату большую, чем средняя зарплата   за 2007 г. или большую чем средняя зарплата за 2008г.
SELECT empno
FROM salary
WHERE salvalue > ANY((SELECT AVG(salvalue) FROM salary WHERE year = 2007), (SELECT AVG(salvalue) FROM salary WHERE year = 2008))
GROUP BY empno;


--5: Найти сведения о номерах сотрудников, получивших зарплату за какой-либо месяц большую, чем средние зарплаты за все годы начислений.
SELECT empno 
FROM salary 
WHERE salvalue > ALL(SELECT AVG(salvalue) FROM salary GROUP BY year) 
GROUP BY empno;

--6: Определить годы, в которые начисленная средняя зарплата была больше средней зарплаты за все годы начислений.
SELECT year
FROM SALARY
GROUP BY year
HAVING(AVG(salvalue)) > (SELECT AVG(salvalue) FROM salary)

--7: Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты. 
SELECT deptno 
FROM DEPT d 
WHERE deptno IN ( 
	SELECT deptno 
	FROM CAREER c
	NATURAL JOIN EMP e
	NATURAL JOIN SALARY s
	WHERE s.salvalue IS NOT NULL);

--8: Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты.
SELECT deptno 
FROM DEPT d 
WHERE EXISTS
	(SELECT deptno FROM CAREER c
	NATURAL JOIN EMP e
	NATURAL JOIN SALARY s
	WHERE d.deptno = c.deptno);

--9: Определить номера отделов, для сотрудников которых не начислялась зарплата.
SELECT deptno 
FROM DEPT d 
WHERE NOT EXISTS
	(SELECT deptno FROM CAREER c
	NATURAL JOIN EMP e
	NATURAL JOIN SALARY s
	WHERE d.deptno = c.deptno);

--10: Вывести сведения о карьере сотрудников с указанием названий и адресов отделов вместо номеров отделов.
SELECT e.empname, d.deptname, d.deptaddr, c.startdate, c.enddate
FROM EMP e
NATURAL JOIN CAREER c
NATURAL JOIN DEPT d

--11: Определить целую часть средних зарплат,  по годам начисления.
SELECT year, CAST(AVG(salvalue) as int) as avg_int_salvalue
FROM SALARY 
GROUP BY year

--12: Разделите сотрудников на возрастные группы: A) возраст 20-30 лет; B) 31-40 лет; C) 41-50;    D) 51-60 или возраст не определён.
SELECT empname,
CASE 
	WHEN MONTHS_BETWEEN(SYSDATE, birthdate) / 12 >= 20 and MONTHS_BETWEEN(SYSDATE, birthdate) / 12 <= 30 
		THEN 'ГРУППА А'
	WHEN MONTHS_BETWEEN(SYSDATE, birthdate) / 12 >= 31 and MONTHS_BETWEEN(SYSDATE, birthdate) / 12 <= 40
		THEN 'ГРУППА B'
	WHEN MONTHS_BETWEEN(SYSDATE, birthdate) / 12 >= 41 and MONTHS_BETWEEN(SYSDATE, birthdate) / 12 <= 50 
		THEN 'ГРУППА С'
	WHEN MONTHS_BETWEEN(SYSDATE, birthdate) / 12 >= 51 and MONTHS_BETWEEN(SYSDATE, birthdate) / 12 <= 60 
		THEN 'ГРУППA D'
	ELSE 'ГРУППА НЕ ОПРЕДЕЛЕНА' 
END AS AGE_GROUP
FROM EMP;

--13: Перекодируйте номера отделов, добавив перед номером отдела буквы BI для номеров <=20,  буквы  LN для номеров >=30.
SELECT 
CASE 
	WHEN deptno <= 20 
		THEN CONCAT('BI', CAST(deptno as VARCHAR(10)))
	WHEN deptno >= 30 
		THEN CONCAT('LN', CAST(deptno as VARCHAR(10)))
END AS deptno_with_prefix
FROM DEPT;

--14: Выдать информацию о сотрудниках из таблицы EMP, заменив отсутствие данного о дате рождения  датой '01-01-1000'.
SELECT empname, empno, COALESCE(birthdate, TO_DATE('01-01-1000', 'dd-mm-yyyy')) AS BIRTHDATE 
FROM EMP;

-- 3_3
--1) Требуется представить имя каждого сотрудника таблицы EMP а также имя его руководителя.
SELECT (A.EMPNAME || ' manager is ' || B.EMPNAME) AS EMP_MANAGER 
FROM EMP A 
JOIN EMP B 
ON A.MANAGER_ID = B.EMPNO
ORDER BY A.MANAGER_ID; 

-- 2) Требуется представить имя каждого сотрудника таблицы EMP (даже сотрудника, которому не назначен руководитель) и имя его руководителя.
SELECT (EMPNAME || ' works for ' || PRIOR EMPNAME) AS EMP_MANAGER
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID; 

-- 3) Требуется показать иерархию от CLARK до JOHN KLINTON.
SELECT LTRIM(SYS_CONNECT_BY_PATH(EMPNAME, ' -> '), ' -> ') AS EMP_TREE
FROM EMP
WHERE EMPNAME = 'JOHN KLINTON'
START WITH EMPNAME = 'CLARK'
CONNECT BY EMPNO = PRIOR MANAGER_ID;

-- 4) Требуется получить результирующее множество, описывающее иерархию всей таблицы.
SELECT (LTRIM(SYS_CONNECT_BY_PATH(EMPNAME, ' -> '), ' -> ')) AS TREE
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID;

-- 5) Требуется показать уровень иерархии каждого сотрудника.
SELECT rpad('*', LEVEL, '*') || EMPNAME AS TREE
FROM EMP
START WITH MANAGER_ID IS NULL
CONNECT BY PRIOR EMPNO = MANAGER_ID
ORDER BY LEVEL;

-- 6) Требуется найти всех служащих, которые явно или неявно подчиняются ALLEN.
SELECT EMPNAME
FROM EMP
START WITH EMPNAME = 'ALLEN'
CONNECT BY PRIOR EMPNO = MANAGER_ID;



-- 3_4
-- 1) Требуется используя значения столбца START_DATE получить дату за десять дней до и после приема на работу, полгода до и после приема на работу, год до и после приема на работу сотрудника JOHN KLINTON.
SELECT STARTDATE, 
ENDDATE,
(STARTDATE - 10) AS BEFORE_10_DAYS, 
(ENDDATE + 10) AS AFTER_10_DAYS,
ADD_MONTHS(STARTDATE, -6) AS BEFORE_6_MONTHS, 
ADD_MONTHS(ENDDATE, 6) AS AFTER_6_MONTHS, 
ADD_MONTHS(STARTDATE, -12) AS BEFORE_12_MONTHS, 
ADD_MONTHS(ENDDATE, 12) AS AFTER_12_MONTHS
FROM CAREER 
WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'JOHN KLINTON');

-- 2) Требуется найти разность между двумя датами и представить результат в днях. Вычислите разницу в днях между датами приема на работу сотрудников JOHN MARTIN и ALEX BOUSH.
SELECT 
((SELECT STARTDATE 
         FROM CAREER 
         WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'ALEX BOUSH')) - 
(SELECT STARTDATE 
        FROM CAREER 
        WHERE EMPNO = (SELECT EMPNO FROM EMP WHERE EMPNAME = 'JOHN MARTIN'))) AS DAYS_BETWEEN
FROM DUAL;

-- 3) Требуется найти разность между двумя датами в месяцах и в годах.
SELECT 
MONTHS_BETWEEN(SYSDATE, TO_DATE('09-25-1998', 'MM-DD-YYYY')) AS MONTHS_BETWEEN, 
(MONTHS_BETWEEN(SYSDATE, TO_DATE('09-25-1998', 'MM-DD-YYYY')) / 12) AS YEARS_BETWEEN 
FROM DUAL;

-- 4) Требуется определить интервал времени в днях между двумя датами. Для каждого сотрудника 20-го отделе найти сколько дней прошло между датой его приема на работу и датой приема на работу следующего сотрудника.
SELECT STARTDATE, 
      ((LEAD(STARTDATE, 1) OVER (ORDER BY STARTDATE)) - STARTDATE) AS DAYS_BETWEEN 
FROM CAREER 
WHERE DEPTNO = '20';

-- 5) Требуется подсчитать количество дней в году по столбцу START_DATE.
SELECT EXTRACT(YEAR FROM STARTDATE) AS YEAR, 
       (ADD_MONTHS(TRUNC(STARTDATE, 'y'), 12) - TRUNC(STARTDATE, 'y')) AS DAYS
FROM CAREER;

-- 6) Требуется разложить текущую дату на день, месяц, год, секунды, минуты, часы. Результаты вернуть в численном виде.
SELECT TO_CHAR(SYSDATE, 'DD.MM.YYYY HH24:MI:SS') AS DATE_CHAR, 
       TO_NUMBER(TO_CHAR(SYSDATE, 'DDMMYYYYHH24MISS')) AS DATE_NUMBER 
FROM DUAL;

-- 7) Требуется получить первый и последний дни текущего месяца.
SELECT TRUNC(LAST_DAY(SYSDATE) - 1, 'mm') AS FIRST_DAY,
       SYSDATE,
       LAST_DAY(SYSDATE) AS LAST_DAY
FROM DUAL;

-- 8) Требуется возвратить даты начала и конца каждого из четырех кварталов данного года.
SELECT LEVEL AS QUARTER,
       ADD_MONTHS(trunc(sysdate, 'YEAR'), (LEVEL - 1) * 3) AS QUARTER_START,
       ADD_MONTHS(trunc(sysdate, 'YEAR'), LEVEL * 3) - 1 AS QUARTER_END
FROM DUAL 
CONNECT BY LEVEL <= 4;

-- 9) Требуется найти все даты года, соответствующие заданному дню недели. Сформируйте список понедельников текущего года.
SELECT * 
FROM (SELECT (trunc(sysdate, 'YEAR') + LEVEL - 1)  AS DAY 
             FROM DUAL
             CONNECT BY LEVEL <= 366)
WHERE TO_CHAR(DAY, 'fmday') = 'monday';

-- 10) Требуется создать календарь на текущий месяц. Календарь должен иметь семь столбцов в ширину и пять строк вниз.
-- 10) Требуется создать календарь на текущий месяц. Календарь должен иметь семь столбцов в ширину и пять строк вниз.
WITH X AS (SELECT * FROM (SELECT TRUNC(SYSDATE, 'MM') + LEVEL - 1 MONTH_DATE,
                                 TO_CHAR(TRUNC(SYSDATE, 'MM') + LEVEL - 1, 'IW') WEEK_NUMBER,
                                 TO_CHAR(TRUNC(SYSDATE, 'MM') + LEVEL - 1, 'DD') DAY_NUMBER,
                                 TO_NUMBER(TO_CHAR(TRUNC(SYSDATE, 'MM')+ LEVEL - 1, 'D')) WEEK_DAY,
                                 TO_CHAR(TRUNC(SYSDATE, 'MM') + LEVEL - 1, 'MM') CURR_MONTH,
                                 TO_CHAR(SYSDATE, 'MM') MONTH
                          FROM DUAL
                          CONNECT BY LEVEL <=31)      
            WHERE CURR_MONTH = MONTH)

SELECT MAX(CASE WEEK_DAY WHEN 2 THEN DAY_NUMBER END) AS MONDAY,
       MAX(CASE WEEK_DAY WHEN 3 THEN DAY_NUMBER END) AS TUESDAY,
       MAX(CASE WEEK_DAY WHEN 4 THEN DAY_NUMBER END) AS WEDNESDAY,
       MAX(CASE WEEK_DAY WHEN 5 THEN DAY_NUMBER END) AS THURSDAY,
       MAX(CASE WEEK_DAY WHEN 6 THEN DAY_NUMBER END) AS FRIDAY,
       MAX(CASE WEEK_DAY WHEN 7 THEN DAY_NUMBER END) AS SATURDAY,
       MAX(CASE WEEK_DAY WHEN 1 THEN DAY_NUMBER END) AS SUNDAY
FROM X
GROUP BY WEEK_NUMBER
ORDER BY WEEK_NUMBER;




