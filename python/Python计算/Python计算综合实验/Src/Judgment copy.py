# from MNIST_test import Net
import torch
from torchvision import transforms
from CNNNet import Net
import cv2
import sys

path = sys.path[0]
data_path = "./../Data"
pic_path = "./../Pic"
network = Net()
network.load_state_dict(torch.load(f"{path}/{data_path}/model.pth"))
data = []

for i in range(10):
    transf = transforms.Compose(
        [transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))]
    )
    image = transf(cv2.imread(f"{path}/{pic_path}/{i}.png", cv2.IMREAD_GRAYSCALE))
    image = torch.unsqueeze(image, 0)
    # image = torch.randn(1, 1, 28, 28)
    data.append(image)
# data.append(cv2.imread(f"{path}/{pic_path}/0.jpg"))

# cv2.namedWindow('image')
# cv2.imshow('image', data[0])
# cv2.waitKey(0)
# cv2.destroyAllWindows()
# print(data[1].shape)
for i in range(10):
    output = network(data[i])
    pred = output.data.max(1, keepdim=True)[1][0][0]
    print(pred)
