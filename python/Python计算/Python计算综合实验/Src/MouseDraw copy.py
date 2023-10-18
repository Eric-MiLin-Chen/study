import cv2
import numpy as np
import sys


def draw_circle(event, x, y, flags, param):
    # 判断事件是否为 Left Button Double Clicck
    # print(event)
    global __img
    global isMouseLBDown
    global color
    global lastPoint

    if event == cv2.EVENT_LBUTTONDOWN:
        # 检测到鼠标左键按下
        # print("mouse down")
        isMouseLBDown = True
        cv2.circle(__img, (x, y), 20, (0, 0, 0), -1)
        lastPoint = (x, y)
    elif event == cv2.EVENT_LBUTTONUP:
        # 检测到鼠标左键抬起
        isMouseLBDown = False
        # print("mouse up")
    elif event == cv2.EVENT_MOUSEMOVE:
        if isMouseLBDown:
            # print("drawing")
            cv2.line(__img, pt1=lastPoint, pt2=(x, y), color=(0, 0, 0), thickness=0)
            lastPoint = (x, y)


path = sys.path[0]
pic_path = "./../Pic"
pic_count = 0
# 创建一个黑色图像，并绑定窗口和鼠标回调函数
__img = np.ones((512, 512, 3), np.uint8)
__img[:] = (255, 255, 255)
cmp = np.ones((512, 512, 3), np.uint8)
cmp[:] = (255, 255, 255)
cv2.namedWindow("image")
# 设置鼠标事件回调
cv2.setMouseCallback("image", draw_circle)


def start():
    while True:
        cv2.imshow("image", __img)
        if cv2.waitKey(1) in (ord("q"), 27):
            break
        if cv2.waitKey(1) == ord("s") and not (__img == cmp).all():
            pic_save = np.zeros((512, 512, 3), np.uint8)
            pic_save[:] = 255
            pic_save = pic_save - __img
            pic_save = cv2.copyMakeBorder(
                pic_save, 64, 64, 64, 64, cv2.BORDER_CONSTANT, value=(0, 0, 0)
            )
            cv2.imwrite(
                f"{path}/{pic_path}/{pic_count}.png",
                cv2.resize(pic_save, (28, 28), interpolation=cv2.INTER_AREA),
            )
            pic_count += 1
            __img[:] = (255, 255, 255)
        if cv2.waitKey(1) == ord("r"):
            __img[:] = (255, 255, 255)

    cv2.destroyAllWindows()


if __name__ == "__main__":
    start()
