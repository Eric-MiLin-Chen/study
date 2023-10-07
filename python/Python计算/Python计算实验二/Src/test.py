import matplotlib.pyplot as plt
import matplotlib
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
# font = {
#     "family": "Sonti"
# }
# matplotlib.rc("font", **font)
x = ['张三', '李四', '-1']
y = [1, 2, 3]
plt.plot(x, y)
plt.show()
