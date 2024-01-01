import configparser
import psycopg2

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

def connect_to_database(config)->psycopg2.connection:
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
    
config = read_config()

# 读取配置文件中的数据库连接信息
conn = connect_to_database(config)

conn.set_client_encoding('utf8')
cur = conn.cursor()

# 创建一个数据库游标
cur = conn.cursor()

# 获取数据库中所有表的名称
cur.execute("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public'")
table_names = cur.fetchall()

# 遍历每个表并读取内容
for table_name in table_names:
    table_name = table_name[0]
    print(f"\nReading data from table: {table_name}")

    # 执行查询
    cur.execute(f"SELECT * FROM {table_name}")

    # 获取查询结果
    rows = cur.fetchall()

    # 打印表头
    col_names = [desc[0] for desc in cur.description]
    print("\t|".join(col_names))
    print("-" * (sum(len(col) for col in col_names) + len(col_names) - 1))

    # 打印每一行的数据
    for row in rows:
        print("\t|".join(str(item) for item in row))

# 关闭游标和连接
cur.close()
conn.close()