-- 1. 视图的创建和撤销
-- 1. 设计每个工程使用零件总数的视图
CREATE VIEW V1 AS
SELECT JNO,SUM(QTY) AS S_NUM
FROM SPJ
GROUP BY JNO;

-- CREATE VIEW

-- 2. 查询零件数大于50的工程号
SELECT JNO FROM V1 WHERE S_NUM > 50;

"""
 jno 
-----
 J4
 J1
 J5
(3 rows)
"""

-- 3. 设计一个提供黄色零件的供应商名和地址
CREATE VIEW V2 AS
SELECT SNAME, SADDR
FROM S, SPJ, P
WHERE S.SNO=SPJ.SNO AND P.PNO=SPJ.PNO AND COLOR = '黄';

-- CREATE VIEW

"""
    sname     |     saddr      
--------------+----------------
 零件制造公司 | 南京东晋路55号
 零件制造公司 | 南京东晋路55号
 零件制造公司 | 南京东晋路55号
(3 rows)
"""

-- 4. 设计一个视图，包括每个工程项目使用零件总数
CREATE VIEW V3 AS 
SELECT JNO, SUM(QTY)
FROM SPJ
GROUP BY JNO;

-- CREATE VIEW

"""
 jno | sum 
-----+-----
 J4  | 300
 J1  | 250
 J5  | 100
 J6  |  28
(4 rows)
"""

-- 5. 设计一个更新限制的上海地区工程视图
CREATE VIEW V4 AS 
SELECT * 
FROM J 
WHERE JCITY='上海'
WITH CHECK OPTION;

-- CREATE VIEW

"""
 jno |  jname   | jcity | balance 
-----+----------+-------+---------
 J1  | 东方明珠 | 上海  |    0.00
 J5  | 明珠线   | 上海  |  123.00
 J6  | 南浦大桥 | 上海  |  234.70
(3 rows)
"""

