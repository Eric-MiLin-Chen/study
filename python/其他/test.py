import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

# 中文和正负号设置
mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

x = np.arange(8)
bar_width = 0.3
tick_label = school_num["城市"]
plt.figure(figsize=(13, 7))
# 柱状
plt.bar(
    x,
    school_num["小学"],
    bar_width,
    align="center",
    color="#2bb179",
    label="小学",
    alpha=0.5,
)
plt.bar(
    x + bar_width,
    school_num["初中"],
    bar_width,
    color="b",
    align="center",
    label="初中",
    alpha=0.5,
)
plt.bar(
    x + bar_width * 2,
    school_num["高中"],
    bar_width,
    color="orange",
    align="center",
    label="高中",
    alpha=0.5,
)
# 折线
plt.plot(
    x + bar_width,
    people_num["人数-万"],
    color="#ff796c",
    marker="o",
    lw=2,
    label="人口普查数(万)",
)

text_x = [x, x + bar_width, x + bar_width * 2]
text_x = [text_x[i][j] for i in range(3) for j in range(8)]
text_y = [school_num["小学"], school_num["初中"], school_num["高中"]]
text_y = [text_y[i][j] for i in range(3) for j in range(8)]
plt.xticks(x + bar_width, tick_label, fontsize=18)
plt.yticks(fontsize=18)
plt.xlabel("城市", fontsize=20)
plt.ylabel("学校数量", fontsize=20)
plt.legend(fontsize=16)
plt.grid()

# 柱型加数字
for x, y, text in zip(text_x, text_y, text_y):
    plt.text(x - 0.12, y + 15, str(text), fontsize=12)

# plt.savefig(r'./并排柱状图示例.png')
