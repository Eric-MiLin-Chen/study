import sys
import numpy as np
import csv
import pandas as pd

# import datetime

# dd = "2019/03/17 11:00:00"
# dd = datetime.datetime.strptime(dd, "%Y/%m/%d %H:%M:%S")
# dd1 = "2019/03/17 11:00:01"
# dd1 = datetime.datetime.strptime(dd1, "%Y/%m/%d %H:%M:%S")
# print(dd1 - dd)


def GetData(filename: str) -> np.ndarray:
    data = []
    with open(filename, "r") as file:
        csv_reader = csv.reader(file)
        for row in csv_reader:
            data.append([float(value) for value in row])
    return np.array(data)


# 读取CSV文件并保存为ndarray
src_path = sys.path[0]
relative_path = "../Data"
csv_file = "shanghaidataset.csv"
# data_ndarray = GetData("/".join([src_path, relative_path, csv_file]))
data_ndarray = pd.read_csv("/".join([src_path, relative_path, csv_file]))

data_ndarray = data_ndarray.loc[
    :,
    [
        "start_time",
        "end_time",
        "start_location_y",
        "start_location_x",
        "end_location_y",
        "end_location_x",
    ],
].to_numpy()
