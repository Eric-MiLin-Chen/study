import configparser
import psycopg2
from pprint import pprint

# 数据库连接参数
def read_config(file_path='./config/config.ini'):
    try:
        # 使用configparser模块读取INI配置文件
        config = configparser.ConfigParser()
        config.read(file_path)
        return config['DATABASE']
    except FileNotFoundError:
        pprint(f"找不到配置文件 '{file_path}'。")
    except Exception as e:
        pprint(f"读取配置文件时发生错误: {e}")
    return None

def connect_to_database(config):
    try:
        # 数据库连接参数
        db_params = {
            'dbname': "school",
            'user': config['DB_USER'],
            'password': config['DB_PASSWORD'],
            'host': config['DB_HOST'],
            'port': config['DB_PORT']
        }
        # 连接到数据库
        conn = psycopg2.connect(**db_params)
        print("成功连接到数据库")
        return conn
    except Exception as e:
        print(f"连接数据库时发生错误: {e}")
        return None

def execute_query(conn, query):
    try:
        # 创建游标
        cur = conn.cursor()
        # 执行查询
        cur.execute(query)
        # 获取查询结果
        result = cur.fetchall()
        # 打印结果
        pprint(result)
        # 提交事务
        conn.commit()
        # 关闭游标
        cur.close()
    except Exception as e:
        pprint(f"执行查询时发生错误: {e}")
        # 发生错误时回滚事务
        conn.rollback()
    finally:
        # 无论是否发生错误，关闭游标
        if cur:
            cur.close()


def main():
# 从INI文件中读取数据库连接信息
    config = read_config()

    # 读取配置文件中的数据库连接信息
    if config:
        # 连接到数据库
        connection = connect_to_database(config)

        if connection:
            # 查询1: 查询每个学生选课情况（包括没有选修课程的学生）
            pprint("查询1: 查询每个学生选课情况（包括没有选修课程的学生）")
            query1 = (
                """
                SELECT S.xh, S.xm, E.kh 
                FROM S LEFT JOIN E ON S.xh = E.xh;
                """
            )
            execute_query(connection, query1)

            # 查询2: 检索所有课程都选修的学生的学号与姓名
            pprint("查询2: 检索所有课程都选修的学生的学号与姓名")
            query2 = (
                """
                SELECT S.xh, S.xm
                FROM S 
                WHERE NOT EXISTS ( 
                    SELECT C.kh 
                    FROM C 
                    WHERE NOT EXISTS ( 
                        SELECT * 
                        FROM E 
                        WHERE E.xh = S.xh AND E.kh = C.kh 
                    ) 
                );
                """
            )
            execute_query(connection, query2)

            # 查询3: 检索选修课程包含1106同学所学全部课程的学生学号和姓名
            pprint("查询3: 检索选修课程包含1106同学所学全部课程的学生学号和姓名")
            query3 = (
                """
                SELECT E1.xh, S.xm 
                FROM E E1 
                JOIN S ON E1.xh = S.xh 
                WHERE NOT EXISTS ( 
                    SELECT C.kh 
                    FROM C 
                    WHERE NOT EXISTS ( 
                        SELECT * 
                        FROM E E2 
                        WHERE E2.xh = E1.xh AND E2.kh = C.kh 
                    ) 
                    AND E1.xh = '1106' 
                );
                """
            )
            execute_query(connection, query3)

            # 查询4: 查询每门课程中分数最高的学生学号和学生姓名
            pprint("查询4: 查询每门课程中分数最高的学生学号和学生姓名")
            query4 = (
                """
                WITH MaxScores AS ( 
                    SELECT kh, MAX(zpcj) AS max_score 
                    FROM E 
                    GROUP BY kh 
                ) 
                SELECT E.xh, S.xm 
                FROM E 
                JOIN MaxScores ON E.kh = MaxScores.kh AND E.zpcj = MaxScores.max_score 
                JOIN S ON E.xh = S.xh;
                """
            )
            execute_query(connection, query4)

            # 查询5: 查询年龄小于本学院平均年龄，所有课程总评成绩都高于所选课程平均总评成绩的学生学号、姓名和平均总评成绩，按年龄排序
            pprint("查询5: 查询年龄小于本学院平均年龄，所有课程总评成绩都高于所选课程平均总评成绩的学生学号、姓名和平均总评成绩，按年龄排序")
            query5 = (
                """
                WITH AvgAge AS ( 
                    SELECT D.yxh, AVG(EXTRACT(YEAR FROM age(current_date, S.csrq))) AS avg_age 
                    FROM S 
                    JOIN D ON S.yxh = D.yxh 
                    GROUP BY D.yxh 
                )
                SELECT E.xh, S.xm, AVG(E.zpcj) AS avg_zpcj, EXTRACT(YEAR FROM age(current_date, S.csrq)) AS age
                FROM E 
                JOIN S ON E.xh = S.xh 
                JOIN AvgAge ON S.yxh = AvgAge.yxh 
                WHERE EXTRACT(YEAR FROM age(current_date, S.csrq)) < AvgAge.avg_age 
                GROUP BY E.xh, S.xm, age 
                HAVING MIN(E.zpcj) > (SELECT AVG(zpcj) FROM E WHERE kh = '08305001') 
                ORDER BY age;
                """
            )
            execute_query(connection, query5)

            # 关闭数据库连接
            connection.close()
            print("数据库连接已关闭")

if __name__ == "__main__":
    main()
