import sys

src_dir = sys.path[0]
Lib_dir = "./../Lib"
sys.path.append(src_dir + "/" + Lib_dir)

from myArray import MyArray
from myMatrix import simNumpyArray

# 创建一个测试数组
arr = MyArray(1, 2, 3, 4, 5)
print(f"Array: {arr}")

# 数组的基本运算
print("Array + 2:", arr + 2)
print("Array - 2:", arr - 2)
print("Array * 2:", arr * 2)
print("Array / 2:", arr / 2)
print("Array // 2:", arr // 2)
print("Array % 2:", arr % 2)
print("Array ** 2:", arr**2)
print("len(Array):", len(arr))
print("Array[2]:", arr[2])
print("Array[2, 3]:", arr[2, 3])
arr.append(0)
print("Array.append(0):", arr)
arr[0] = 10
print("Array[len(Array) - 1] = 10:", arr)
print("10 in Array:", 10 in arr)
print("Array.dot(Array):", arr.dot(arr))

# 创建两个2x2的矩阵
a = simNumpyArray([1, 2, 3, 4])
b = simNumpyArray([5, 6, 7, 8])
print(list(map(str, [[5], [6], [7], [8]])))
print("a: ", a)
print("b: ", b)

# 输出变形后的矩阵
a.reshape((2, -1))
b.reshape((2, -1))
print(f"a.reshape(2, -1): \n{a}")
print(f"b.reshape(2, -1): \n{b}")

# 输出矩阵的转置
print(f"a的转置: \n{a.T}")
print(f"b的转置: \n{b.T}")

print(f"a + b: \n{a + b}")
print(f"a - b: \n{a - b}")
print(f"a * 2: \n{a * 2}")
print(f"a * b: \n{a * b}")
print(f"a / 2: \n{a / 2}")
print(f"a // 2: \n{a // 2}")
print(f"a ** 2: \n{a**2}")
print(f"a * b: \n{a * b}")
print(f"a == b: \n{a == b}")
print(f"a < b: \n{a < b}")
print(f"print(i for i in a, end=''): \n{[i for i in a]}")
print(f"a.Sin:  \n{a.Sin}")
print(f"a.Cos:  \n{a.Cos}")
