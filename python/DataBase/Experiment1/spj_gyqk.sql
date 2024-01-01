create database gyqk;
\c gyqk;

create table s
( sno   char(2) not null primary key,
  sname varchar(50) not null,
  saddr varchar(100));
insert into s values('S1','原料公司','南京北门23号');
insert into s values('S2','红星钢管厂','上海浦东100号');
insert into s values('S3','零件制造公司','南京东晋路55号');
insert into s values('S4','配件公司','江西上饶58号');
insert into s values('S5','原料公司','北京红星路88号');
insert into s values('S8','东方配件厂','天津叶西路100号');

create table p
( pno    char(2) not null primary key,
  pname  char(4),
  color  char(2) default '黑',
  weight int);
insert into p values('P1','钢筋','黑',25);
insert into p values('P2','钢管','白',26);
insert into p values('P3','螺母','红',11);
insert into p values('P4','螺丝','黄',12);
insert into p values('P5','齿轮','红',18);

create table j
( jno    char(2) not null primary key,
  jname  varchar(20),
  jcity  char(4) default '上海',
  balance numeric(6,2));
insert into j values('J1','东方明珠','上海',0.00);
insert into j values('J2','炼油厂','长春',-11.20);
insert into j values('J3','地铁三号','北京',678.00);
insert into j values('J4','炼钢工地','天津',456.00);
insert into j values('J5','明珠线','上海',123.00);
insert into j values('J6','南浦大桥','上海',234.70);
insert into j values('J7','红星水泥厂','江西',343.00);

create table spj
( sno char(2) not null references s(sno),
  pno char(2) not null references p(pno),
  jno char(2) not null references j(jno),
  price numeric(4,2) check(price>0),
  qty int check(qty between 0 and 10000),
  primary key(sno,pno,jno));
insert into spj values('S1','P1','J1',22.60,80);
insert into spj values('S1','P1','J4',22.60,60);
insert into spj values('S1','P3','J1',22.80,100);
insert into spj values('S1','P3','J4',22.80,60);
insert into spj values('S3','P3','J5',22.10,100);
insert into spj values('S3','P4','J1',11.90,30);
insert into spj values('S3','P4','J4',11.90,60);
insert into spj values('S4','P2','J4',33.80,60);
insert into spj values('S5','P5','J1',22.80,20);
insert into spj values('S5','P5','J4',22.80,60);
insert into spj values('S8','P3','J1',13.00,20);
insert into spj values('S1','P3','J6',22.80,6);
insert into spj values('S3','P4','J6',11.90,6);
insert into spj values('S4','P2','J6',33.80,8);
insert into spj values('S5','P5','J6',22.80,8);



