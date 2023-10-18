import numpy as np
import matplotlib.pyplot as plt
import sys


src_path = sys.path[0]
relative_path = "../../../Data"
data = ""
worst = ""
with open("/".join([src_path, relative_path, "file.txt"]), 'r') as file:
    data = file.read()
with open("/".join([src_path, relative_path, "worst.txt"]), 'r') as file:
    worst = file.read()

data = np.array(list(map(float, data.split())))
data = data.reshape(3, 3, 2, 9)
print(data)
worst = np.array(list(map(int, worst.split())))
worst = worst.reshape(3, 3, 9)
print(worst)

size = [pow(2, i + 5) for i in range(9)]
DataName = ["OrderedData", "NormalOrderedData", "RandomOrderedData"]
FuncName = ["BinarySearch", "FibSearch", "InterpolationSearch"]
color = ["#e47e72", "#87c982", "#27a0e7"]
style = ['o-', 's-', 'D-']

for j in range(2):
    plt.figure(figsize=(10, 6))
    for f in range(3):
        for i in range(3):
            plt.plot(size, data[f][i][j], style[i], color=color[f], label=FuncName[f] +
                     " " + DataName[i])
    plt.xlabel("Data Size")  # 横坐标名字
    plt.ylabel("Compare Counts")  # 纵坐标名字
    plt.legend(loc="best")  # 图例
    plt.savefig("/".join([src_path, "../../../Img",
                f"Three Functions{j + 1}.png"]), dpi=600)
    plt.close()

j = 0
plt.figure(figsize=(10, 6))
for f in range(3):
    for i in range(3):
        plt.plot(size, data[f][i][j], style[i], color=color[f], label=FuncName[f] +
                 " " + DataName[i])
        plt.plot(size, worst[f][i], style[i][0]+':', color=color[f])
plt.xlabel("Data Size")  # 横坐标名字
plt.ylabel("Compare Counts")  # 纵坐标名字
plt.legend(loc="best")  # 图例
plt.savefig("/".join([src_path, "../../../Img",
            f"Three Functions{j + 1} with worst.png"]), dpi=600)
plt.close()

for f in range(3):
    for j in range(2):
        plt.figure(figsize=(10, 6))
        for i in range(3):
            plt.plot(size, data[f][i][j], style[i], color=color[f], label=FuncName[f] +
                     " " + DataName[i])
            if j == 0:
                plt.plot(size, worst[f][i], style[i][0]+':', color=color[f])
        plt.xlabel("Data Size")  # 横坐标名字
        plt.ylabel("Compare Counts")  # 纵坐标名字
        plt.legend(loc="best")  # 图例
        plt.savefig("/".join([src_path, "../../../Img",
                    f"Different Data of {FuncName[f]}{j + 1}.png"]), dpi=600)
        plt.close()

for i in range(3):
    for j in range(2):
        plt.figure(figsize=(10, 6))
        for f in range(3):
            plt.plot(size, data[f][i][j], style[i], color=color[f], label=FuncName[f] +
                     " " + DataName[i])
            if j == 0:
                plt.plot(size, worst[f][i], style[i][0]+':', color=color[f])
        plt.xlabel("Data Size")  # 横坐标名字
        plt.ylabel("Compare Counts")  # 纵坐标名字
        plt.legend(loc="best")  # 图例
        plt.savefig("/".join([src_path, "../../../Img",
                    f"Different Function of {DataName[i]}{j + 1}.png"]), dpi=600)
        plt.close()
