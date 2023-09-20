import numpy as np
import matplotlib.pyplot as plt
import sys

src_path = sys.path[0]
relative_path = "../../Data"
data = ""
with open("/".join([src_path, relative_path, "File.txt"]), "r") as file:
    data = file.read()

data = np.array(list(map(float, data.split())))
data = data.reshape(8, 4, 2, 9)
# Function TestFileType CompareCount/MoveCount TestFileSize
print(data)

DataSize = [pow(2, i + 5) for i in range(9)]
DataType = ["PartiallySortedData", "RandomData", "ReversedData", "SortedData"]
FuncName = [
    "insertionSort",
    "shellSort",
    "bubbleSort",
    "quickSort",
    "selectionSort",
    "heapSort",
    "mergeSort",
    "radixSort",
]
DataName = ["CompareNum", "MoveNum"]
color = ["#e47e72", "#87c982", "#27a0e7", "#828282"]
bar_width = 0.2
Summery = [[], []]
x = np.arange(9)


# 柱状
def SaveImg():
    for funcname in range(len(FuncName)):
        for dataname in range(len(DataName)):
            plt.figure(figsize=(10, 6))
            for datatype in range(len(DataType)):
                bar = plt.bar(
                    x + datatype * bar_width,
                    data[funcname][datatype][dataname],
                    bar_width,
                    align="center",
                    color=color[datatype],
                    label=DataType[datatype],
                    alpha=0.5,
                )
                plt.bar_label(bar, rotation=90, fontsize=8)

            temp = [data[funcname][i][dataname] for i in range(len(DataType))]
            temp = [
                sum([temp[i][j] / 4 for i in range(len(DataType))])
                for j in range(len(DataSize))
            ]
            Summery[dataname].append(temp)
            plt.plot(
                x + 1.5 * bar_width,
                temp,
                "o-",
                color="r",
                label=f"Average {DataType[datatype]}",
                alpha=0.5,
            )

            plt.title(f"{FuncName[funcname]} {DataName[dataname]}", fontsize=18)
            plt.xticks(x + 1.5 * bar_width, DataSize, fontsize=12)
            plt.xlabel("Data Size", fontsize=14)
            plt.ylabel(DataName[dataname], fontsize=14)
            plt.legend(loc="best")
            plt.savefig(
                "/".join(
                    [
                        src_path,
                        "../../Img",
                        f"{FuncName[funcname]} {DataName[dataname]}.png",
                    ]
                ),
                dpi=150,
            )
            plt.close()


SaveImg()

for dataname in range(len(DataName)):
    plt.figure(figsize=(10, 6))
    for funcname in range(len(FuncName)):
        plt.plot(
            DataSize,
            Summery[dataname][funcname],
            "o-",
            # color="r",
            label=f"Average {FuncName[funcname]}",
            alpha=0.8,
        )

        plt.title(f"Summery {DataName[dataname]}", fontsize=18)
        plt.xlabel("Data Size", fontsize=14)
        plt.ylabel(DataName[dataname], fontsize=14)
        plt.legend(loc="best")
    plt.savefig(
        "/".join(
            [
                src_path,
                "../../Img",
                f"Summery {DataName[dataname]}.png",
            ]
        ),
        dpi=150,
    )
    plt.show()
    plt.close()
