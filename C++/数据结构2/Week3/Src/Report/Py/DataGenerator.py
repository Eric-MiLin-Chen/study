import numpy as np
import sys


def RandomOrderedData(low: int, high: int, size: int) -> list[int]:
    return list(np.sort(np.random.randint(low, high, size)))


def NormalOrderedData(low: int, high: int, size: int) -> list[int]:
    tmp = np.sort(np.random.normal(0, 1, size))
    return list(map(lambda a: int((a * (high - low) + low * tmp[-1] - high * tmp[0]) / (tmp[-1] - tmp[0])), tmp))


def OrderedData(low: int, high: int, size: int) -> list[int]:
    return list(range(low, high, (high - low) // size))


def SaveData(filename, data):
    src_path = sys.path[0]
    relative_path = "../../../Data"
    with open("/".join([src_path, relative_path, filename + str(len(data))+".txt"]), 'w') as file:
        file.write(" ".join(map(str, data)))

size = 32
for i in range(9):
    SaveData("RandomOrderedData", RandomOrderedData(0, 10 * size, size))
    SaveData("NormalOrderedData", NormalOrderedData(0, 10 * size, size))
    SaveData("OrderedData", OrderedData(0, 10 * size, size))
    size *= 2
