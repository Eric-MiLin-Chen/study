import psycopg2
import numpy as np
import time
import configparser

# 数据库连接参数
def read_config(file_path='./config/config.ini'):
    try:
        # 使用configparser模块读取INI配置文件
        config = configparser.ConfigParser()
        config.read(file_path)
        return config['DATABASE']
    except FileNotFoundError:
        print(f"找不到配置文件 '{file_path}'。")
    except Exception as e:
        print(f"读取配置文件时发生错误: {e}")
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

# 连接数据库
config = read_config()

# 连接到数据库
conn = connect_to_database(config)

conn.set_client_encoding('utf8')

# 创建游标
cursor = conn.cursor()

# 移除数据库
# drop_index_queries = "DROP TABLE IF EXISTS test_table;"
# cursor.execute(drop_index_queries)
# conn.commit()

# 检查表是否已存在
check_table_query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = 'test_table');"
cursor.execute(check_table_query)
table_exists = cursor.fetchone()[0]

if not table_exists:
    # 表不存在，创建表
    create_table_query = """
    CREATE TABLE test_table (
        id SERIAL PRIMARY KEY,
        value INT
    );
    """

    cursor.execute(create_table_query)
    conn.commit()

    # 使用 NumPy 生成1000万个随机整数
    start_time = time.time()
    random_values = np.random.randint(1, 1000, size=(10000000,))
    data_to_insert = [(int(value),) for value in random_values.tolist()]  # 将 NumPy int64 转换为 Python int

    insert_data_query = "INSERT INTO test_table (value) VALUES (%s);"
    cursor.executemany(insert_data_query, data_to_insert)
    conn.commit()
    end_time = time.time()
    print(f"生成并插入数据使用时间: {end_time - start_time} seconds")


# 要执行的随机查询次数
num_queries = 10
total_execution_time_no_index = 0
total_execution_time_with_index = 0

# 创建不同的索引
create_index_queries = [
    "CREATE INDEX idx_value ON test_table(value);",
    "CREATE INDEX idx_id ON test_table(id);"
]

for create_index_query in create_index_queries:
    cursor.execute(create_index_query)
    conn.commit()

    for _ in range(num_queries):
        # 执行一个不使用索引的随机查询
        query_without_index = f"SELECT * FROM test_table WHERE value = {np.random.randint(1, 1000)};"

        start_time = time.time()
        cursor.execute(query_without_index)
        result_without_index = cursor.fetchall()
        end_time = time.time()

        execution_time = end_time - start_time
        total_execution_time_no_index += execution_time

        print(f"执行不使用索引的随机查询所用时间：{execution_time} 秒")
        print(f"不使用索引时检索到的行数：{len(result_without_index)}")

        # 执行一个使用索引的随机查询
        query_with_index = f"SELECT * FROM test_table WHERE id = {np.random.randint(1, 1000)};"

        start_time = time.time()
        cursor.execute(query_with_index)
        result_with_index = cursor.fetchall()
        end_time = time.time()

        execution_time = end_time - start_time
        total_execution_time_with_index += execution_time

        print(f"执行使用索引的随机查询所用时间：{execution_time} 秒")
        print(f"使用索引时检索到的行数：{len(result_with_index)}")

# 计算并打印平均时间
average_execution_time_no_index = total_execution_time_no_index / (num_queries * len(create_index_queries))
average_execution_time_with_index = total_execution_time_with_index / (num_queries * len(create_index_queries))

print(f"\n执行 {num_queries} 次不使用索引的查询的平均时间：{average_execution_time_no_index} 秒")
print(f"执行 {num_queries} 次使用索引的查询的平均时间：{average_execution_time_with_index} 秒")

# 移除索引
drop_index_queries = [
    "DROP INDEX IF EXISTS idx_value;",
    "DROP INDEX IF EXISTS idx_id;"
]

for drop_index_query in drop_index_queries:
    cursor.execute(drop_index_query)
    conn.commit()

# 关闭连接
cursor.close()
conn.close()
