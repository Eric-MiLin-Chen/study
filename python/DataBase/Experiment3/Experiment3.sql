-- 1. 验证在1000万个以上记录时在索引和不索引时的查询时间区别
-- ./1.py

----------------------------------------------------------------
-- 2. 检索年龄大于22岁的男学生的学号与姓名
SELECT S.xh, S.xm
FROM S
WHERE 
    DATE_TRUNC('year', AGE(TIMESTAMP '2011-09-01', S.csrq)) >= INTERVAL '20 years' AND
    S.xb = '男';

----------------------------------------------------------------
-- 3. 检索刘晓明不学的课程的课程号
SELECT DISTINCT
    C.kh AS 课号,
    C.km AS 课名
FROM C
WHERE C.kh NOT IN (
    SELECT DISTINCT E.kh
    FROM S, E
    WHERE S.xm = '刘晓明' AND E.xh = S.xh);

----------------------------------------------------------------
-- 4. 检索马小红老师所授课程的学年，学期，课程号，上课时间
SELECT DISTINCT 
    T.xm AS 姓名,
    O.kh AS 课号,
    SUBSTRING(O.xq FROM 1 FOR 9) AS 学年,
    SUBSTRING(O.xq FROM 11 FOR 4) AS 学期,
    O.sksj AS 上课时间,
    c.km AS 课名
FROM
    T, C, O
WHERE
    T.xm = '马小红' AND
    T.gh = O.gh AND 
    O.kh = C.kh;

----------------------------------------------------------------
-- 5. 查询计算机学院男生总评成绩及格、教授开设的课程的课程号、课名、开课教师姓名，按开课教师升序，课程号降序排序
SELECT
    C.kh AS 课号, 
    C.km AS 课名, 
    T.xm AS 姓名
FROM 
    C, T, S, E, D
WHERE 
    S.xb = '男' AND 
    T.xl = '教授' AND 
    E.zpcj >= 60 AND 
    S.xh = E.xh AND 
    T.gh = E.gh AND 
    E.kh = C.kh AND
    S.yxh = D.yxh AND
    D.mc = '计算机学院'
ORDER BY
    T.xm ASC, 
    E.kh DESC;

----------------------------------------------------------------
-- 6. 检索学号比张颖同学大，年龄比张颖同学小的同学学号、姓名
SELECT
    S.xh AS 学号,
    S.xm AS 姓名
FROM S
WHERE
    S.xh > (SELECT S.xh FROM S WHERE S.xm = '张颖') AND
    S.csrq > (SELECT S.csrq FROM S WHERE S.xm = '张颖');

----------------------------------------------------------------
-- 7. 检索同时选修了“08305001”和“08305002”的学生学号和姓名
SELECT DISTINCT ON (S.xh)
    S.xh AS 学号,
    S.xm AS 姓名
FROM E AS E1
JOIN S ON E1.xh = S.xh
JOIN E AS E2 ON
    E1.xh = E2.xh AND
    E1.kh = 08305001 AND 
    E2.kh = 08305002;