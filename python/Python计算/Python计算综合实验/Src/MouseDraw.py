import cv2
import numpy as np
import sys
import torch
from torchvision import transforms
from CNNNet import Net


font = cv2.FONT_HERSHEY_SIMPLEX
font_size = 1
color = (0, 0, 0)
position = (50, 150)
isMouseLBDown = False


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
            cv2.line(__img, pt1=lastPoint, pt2=(x, y), color=(0, 0, 0), thickness=40)
            lastPoint = (x, y)


path = sys.path[0]
pic_path = "./../Pic"

# 创建一个黑色图像，并绑定窗口和鼠标回调函数
__img = np.ones((512, 512, 3), np.uint8)
__img[:] = (255, 255, 255)
cmp = np.ones((512, 512, 3), np.uint8)
cmp[:] = (255, 255, 255)
cv2.namedWindow("image")
cv2.imshow("image", __img)
# 设置鼠标事件回调
cv2.setMouseCallback("image", draw_circle)
# 载入模型
path = sys.path[0]
data_path = "./../Data"
network = Net()
network.load_state_dict(torch.load(f"{path}/{data_path}/model.pth"))
transf = transforms.Compose(
    [transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))]
)


def start():
    while True:
        cv2.imshow("image", __img)
        if cv2.waitKey(1) in (ord("q"), 27):
            break
        if cv2.waitKey(1) == ord("s") and not (__img == cmp).all():
            pic_save = np.zeros((512, 512, 3), np.uint8)
            pic_save[:] = 255
            pic_save = pic_save - __img
            __img[:] = (255, 255, 255)
            pic_save = cv2.copyMakeBorder(
                pic_save, 64, 64, 64, 64, cv2.BORDER_CONSTANT, value=(0, 0, 0)
            )
            pic_save = cv2.resize(pic_save, (28, 28), interpolation=cv2.INTER_AREA)
            pic_save = transf(cv2.cvtColor(pic_save, cv2.COLOR_BGR2GRAY))
            pic_save = torch.unsqueeze(pic_save, 0)
            output = network(pic_save)
            pred = output.data.max(1, keepdim=True)[1][0][0]
            cv2.namedWindow("Result")
            temp = 255 * np.ones((300, 500, 3), dtype=np.uint8)
            cv2.putText(
                temp, f"Number: {int(pred)}", position, font, font_size, color, 2
            )
            cv2.imshow("Result", temp)
            if (cv2.waitKey(1) & 0xFF) in (13, 27):
                cv2.destroyWindow("Result")
        if cv2.waitKey(1) == ord("r"):
            __img[:] = (255, 255, 255)

    cv2.destroyAllWindows()


if __name__ == "__main__":
    start()
