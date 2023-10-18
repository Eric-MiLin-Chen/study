import numpy as np
import sys


# 生成正序数据
def generate_sorted_data(size: int):
    return list(np.arange(size))


# 生成逆序数据
def generate_reverse_data(size: int):
    return list(np.arange(size, 0, -1))


# 生成基本有序数据
def generate_partially_sorted_data(size: int):
    data = np.arange(size)
    # 随机打乱部分数据
    np.random.shuffle(data[: int(size * 0.1)])
    return list(data)


# 生成完全随机数据
def generate_random_data(size: int):
    return list(np.random.randint(0, size, size=size))


# 保存到文件
def SaveData(filename: str, data: list[int]):
    src_path = sys.path[0]
    relative_path = "../../Data"
    with open(
        "/".join([src_path, relative_path, filename + str(len(data)) + ".txt"]), "w"
    ) as file:
        file.write(" ".join(map(str, data)))


# 调用函数生成数据
size = 32
for i in range(9):
    SaveData("SortedData", generate_sorted_data(size))
    SaveData("ReversedData", generate_reverse_data(size))
    SaveData("PartiallySortedData", generate_partially_sorted_data(size))
    SaveData("RandomData", generate_random_data(size))
    size *= 2
