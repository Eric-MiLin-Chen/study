-- 1. 全称量词
-- 1. 查询使用了全部零件的工程名称(理解为: 没有零件是不用的)
select jno,jname     --找工程名称 
from j  
where not exists (   ---不存在一个零件 
    select *  
    from p  
    where not exists (    ---这个工程没有使用 
        select *  
        from spj
        where 
            spj.jno=j.jno and 
            spj.pno=p.pno));   --工程使用某个零件

-- 2. 查询至少用了供应商S1所供应的的全部零件的工程号
select jno        --找工程号
from spj as a 
where not exists (  --不存在一个零件
    select *
    from spj as b
    where 
        b.sno='S1' and   --是供应商‘S1’供应
        not exists (    --而这个工程没有用
            select *       
        from spj as c        
            where 
                c.jno=a.jno and 
                c.pno=b.pno));
----------------------------------------------------------------
-- 2. 聚合函数
-- 例1.查询供应商提供的商品种类, 数量, 平均金额
select 
    count(distinct pno) as 种类,
    SUM(qty) as 数量,
    AVG(price) as 平均金额
from spj;

-- 例2.查询供应商提供的商品次数
select COUNT(*) from spj;

----------------------------------------------------------------
-- 3. 对查询结果分组
-- 例：查询每个供应商提供的商品种类, 数量, 平均金额
select 
    count(distinct pno),
    SUM(qty),
    AVG(price) 
from spj  
group by sno;

-- 查询每个供应商的名称及其提供的商品种类, 商品数量, 平均金额 
select 
    sname, 
    count(distinct pno), 
    SUM(qty),
    AVG(price) 
from spj,s 
where spj.sno=s.sno 
group by s.sno, s.sname;

----------------------------------------------------------------
-- 对分组结果筛选
-- 例1.查询提供两种或两种以上商品的供应商号
select sno 
from spj
group by sno
having COUNT(distinct pno)>=2;

-- 例2.查询所有单价都超过22元的商品号和商品名称
select pno 
from spj 
where price=(select max(price) from spj);

-- 例3.查询单价最贵的商品编号
select spj.pno,p.pname
from spj,p
where spj.pno = p.pno
group by spj.pno,p.pname
having MIN(price) > 22;

----------------------------------------------------------------
-- 对查询结果排序
-- 例：统计上海地区的工程使用零件种数（超过三种）和零件数量要求按种数升序, 总数量降序排列
select
    spj.jno,
    j.jname,
    COUNT(distinct pno) as zs,
    SUM(QTY) as total  
from spj,j  
where
    spj.jno = j.jno and
    j.jcity = '上海' 
group by spj.jno,j.jname  
having count(distinct pno)>3
order by zs asc, total des;

----------------------------------------------------------------
-- 集合查询
-- 例1.查询价格在0-30,31-60,61-80,81-100间的平均单价
select '0-30' as qujian,AVG(price) as avgprice from spj where price between 0 and 30 
union 
select '31-60' as qujian,AVG(price) as avgprice from spj where price between 31 and 60 
union 
select '61-80' as qujian,AVG(price) as avgprice from spj where price between 61 and 80 
union 
select '81-100' as qujian,AVG(price) as avgprice from spj where price between 81 and 100;

-- 例：查询使用了红色和蓝色零件的工程号 
select distinct jno
from spj,p
where 
    spj.pno = p.pno and 
    p.color = '红'
intersect
select distinct jno 
from spj,p
where 
    spj.pno = p.pno and 
    p.color='蓝';

-- 例：检索不使用编号为P3零件的工程编号和名称 
select distinct jno from j
except
select distinct jno from spj where pno='P3'

----------------------------------------------------------------
-- 数据更新
-- 单记录插入：没有列名表表示插入的是表的所有属性
insert into j(jno,jname,jcity) values('J8','地铁两号线','上海');

-- 多记录插入
insert into spj(sno,pno,jno,qty)  
select sno,pno,'J7',60 from spj where jno='J1';

-- 修改记录
-- 例：当S3提供的P5零件的单价低于该零件的平均单价时, 将其提高8%
update spj set price=price*1.08
where 
    sno='S3' and pno='P5' and 
    price<(select AVG(price) from spj where pno='P5');

-- 删除记录
-- 例：删除红色零件 
delete from p where p.color='红色';

----------------------------------------------------------------
-- 1. 建立一个视图, 能够从其中查询每一个学生的学号、姓名、其上的课的名称以及每门课的总评成绩
CREATE VIEW bjg AS
SELECT
    S.xh AS "学号",
    S.xm AS "姓名",
    C.km AS "课名",
    E.zpcj AS "总评成绩"
FROM public.S, public.E, public.C
WHERE
    S.xh = E.xh AND
    E.kh = C.kh AND
    (E.zpcj < 60 OR E.zpcj IS NULL);

SELECT * FROM BJG;

----------------------------------------------------------------
-- 2. 在E表中插入记录, 把每个学生没学过的课程都插入到E表中, 使得每个学生都选修每门课
INSERT INTO E(xh, xq, kh, gh)
SELECT S.xh, O.xq, O.kh, O.gh
FROM S, O
WHERE O.kh NOT IN (
    SELECT E.kh 
    FROM E 
    WHERE 
        S.xh = E.xh AND 
        O.kh = E.kh
);

            
----------------------------------------------------------------
-- 3. 求年龄大于所有女同学年龄的男学生姓名和年龄
SELECT
    S.xm,
    EXTRACT(YEAR FROM CURRENT_DATE) - EXTRACT(YEAR FROM S.csrq) AS age
FROM S
WHERE
    S.xb = '男' AND
    (EXTRACT(YEAR FROM CURRENT_DATE) - EXTRACT(YEAR FROM S.csrq)) > (
        SELECT MAX(EXTRACT(YEAR FROM CURRENT_DATE) - EXTRACT(YEAR FROM S.csrq))
        FROM S
        WHERE S.xb = '女'
    );


----------------------------------------------------------------
-- 4. 在E表中修改08305001课程的平时成绩, 若成绩小于等于75分时提高5%, 若成绩大于75分时提高4%
UPDATE E SET E.pscj = E.pscj * 1.04 WHERE E.pscj > 75;
UPDATE E SET E.pscj = E.pscj * 1.05 WHERE E.pscj <= 75;

----------------------------------------------------------------
-- 5. 删除没有开课的学院

-- 单独运行删除学院报错:
-- ERROR:  update or delete on table "d" violates foreign key constraint "c_yxh_fkey" on table "c"
-- DETAIL:  Key (yxh)=(03) is still referenced from table "c".

DELETE FROM C
WHERE yxh NOT IN (
    SELECT yxh FROM T, O WHERE T.gh = O.gh
);

DELETE FROM D WHERE yxh NOT IN (
    SELECT yxh FROM T, O WHERE T.gh = O.gh
);

----------------------------------------------------------------
-- 6. 查询优、良、中、及格、不及格学生人数
SELECT
    SUM(CASE WHEN E.zpcj < 60 OR E.zpcj IS NULL THEN 1 ELSE 0 END) AS 不及格, 
    SUM(CASE WHEN E.zpcj >= 60 AND E.zpcj < 70 AND E.zpcj IS NOT NULL THEN 1 ELSE 0 END) AS 及格,
    SUM(CASE WHEN E.zpcj >= 70 AND E.zpcj < 80 AND E.zpcj IS NOT NULL THEN 1 ELSE 0 END) AS 中,
    SUM(CASE WHEN E.zpcj >= 80 AND E.zpcj < 90 AND E.zpcj IS NOT NULL THEN 1 ELSE 0 END) AS 良,
    SUM(CASE WHEN E.zpcj >= 90 AND E.zpcj IS NOT NULL THEN 1 ELSE 0 END) AS 优
FROM E;