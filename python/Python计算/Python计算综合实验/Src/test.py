import cv2
import numpy as np

# 创建一个空白图像作为画布
image = 255 * np.ones((300, 500, 3), dtype=np.uint8)

# 显示空白图像窗口
cv2.imshow("Image", image)

# 循环等待键盘事件
while True:
    key = cv2.waitKey(1) & 0xFF

    # 如果按下q键，退出循环
    if key == ord("q"):
        break

    # 输出字符到图像上
    character = chr(key)
    cv2.putText(
        image, character, (50, 150), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2
    )

    # 显示更新后的图像窗口
    cv2.imshow("Image", image)

# 释放窗口资源
cv2.destroyAllWindows()
