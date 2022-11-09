import window
import cv2
import time
import win32gui
import numpy as np


image = cv2.imread("./src/offline-sprite-2x.png")
image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
im = image[29:29+21,954:954+381]
print(im)
maskGameover = np.array(im) / 83

while True:
    cv2.imshow("frame1",im)

    key= cv2.waitKey(1) & 0xFF
    if cv2.getWindowProperty("frame1", cv2.WND_PROP_VISIBLE) <1:
        break
