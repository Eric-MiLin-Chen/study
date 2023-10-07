# %%
from ctypes import string_at
import numpy as np
a = np.array([[0, 1, 2, 3], [4, 5, 6, 7], [8, 9, 10, 11]])
a

# %%
a.dtype


# %%
a[1, 2]

# %%
a[:, 1:3]


# %%
a.ndim


# %%
a.shape


# %%
a.strides


# %%
b = a.reshape(4, 3)
b

# %%
# reshape操作产生的是view视图，只是对数据的解释方式发生变化，数据物理地址相同
a.ctypes.data


# %%
b.ctypes.data


# %%
id(a) == id(b)


# %%
# 数据在内存中连续存储
string_at(b.ctypes.data, b.nbytes).hex()


# %%
# b的转置c，c仍共享相同的数据block，只改变了数据的解释方式，“以列优先的方式解释行优先的存储”
c = b.T
c

# %%
c.ctypes.data


# %%
string_at(c.ctypes.data, c.nbytes).hex()


# %%
a


# %%
# copy会复制一份新的数据，其物理地址位于不同的区域
c = b.copy()
c


# %%
c.ctypes.data


# %%
string_at(c.ctypes.data, c.nbytes).hex()


# %%
# slice操作产生的也是view视图，仍指向原来数据block中的物理地址
d = b[1:3, :]
d


# %%
d.ctypes.data


# %%
print('data buff address from {0} to {1}'.format(
    b.ctypes.data, b.ctypes.data + b.nbytes))
