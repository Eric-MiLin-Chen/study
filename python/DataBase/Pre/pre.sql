\c school

\d e

\d c

SELECT * FROM E;
-- 发现除总评成绩不及格外，也存在成绩为NULL的情况，应同样判断为需要重修

SELECT * FROM C;

SELECT DISTINCT
    E.xq AS 学期,
    E.gh AS 工号,
    E.zpcj AS 总评成绩
FROM E
WHERE
    E.zpcj IS NULL OR E.zpcj < 60;
-- 成功筛选需要重修的课程

SELECT DISTINCT
-- 需要查询学期，课程名与工号
    E.xq AS 学期,
    C.km AS 课程名,
    E.gh AS 工号
FROM
    E
JOIN
    C ON E.kh = C.kh
-- 联结表C查询同课号表项，确定课程名
WHERE
    E.zpcj IS NULL OR E.zpcj < 60;
-- 需要确认重修课程，因此需要查询E.zpxj(总评成绩)

----------------------------------------------------------------

SELECT C.kh, C.km FROM C;
-- 查询课程号与课程名称，准备筛选总评成绩不合格的课程

SELECT DISTINCT
    E.xq AS 学期,
    (SELECT km FROM C WHERE C.kh = E.kh) AS 课程名,
    -- 筛选总评成绩不合格的E表项中的课程名称
    E.gh AS 工号
FROM
    E
WHERE
    E.zpcj IS NULL OR E.zpcj < 60;

----------------------------------------------------------------

SELECT DISTINCT E.xq, C.km, O.gh
FROM E
JOIN C ON E.kh = C.kh
JOIN O ON E.kh = O.kh AND E.gh = O.gh AND E.xq = O.xq
WHERE E.zpcj < 60 OR E.zpcj IS NULL;

----------------------------------------------------------------

SELECT DISTINCT O.xq, C.km, O.gh
FROM O
JOIN C ON O.kh = C.kh
WHERE EXISTS (
    SELECT 1
    FROM E
    WHERE E.kh = O.kh
      AND E.gh = O.gh
      AND E.xq = O.xq
      AND (E.zpcj < 60 OR E.zpcj IS NULL)
);

select distinct 
    e.xh 
from e 
join e as e2 
on e.xh = e2.xh and e.kh = 08305001 and e2.kh = 08305002;