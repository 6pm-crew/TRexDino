import window
import cv2
import time
import win32gui
import numpy as np

print("running")
ESC_KEY=27
FRAME_RATE = 90
SLEEP_TIME = 1/FRAME_RATE

capture = window.WindowCapture("T-Rex Game",FRAME_RATE)

while True:
    start=time.time()
    frame = capture.screenshot()
    x_train = np.array(frame)
    print(x_train.shape)
    cv2.imshow("frame1",frame)
    delta= time.time()-start
    # if delta <SLEEP_TIME:
    #     time.sleep(SLEEP_TIME-delta)
    key= cv2.waitKey(1) & 0xFF
    if cv2.getWindowProperty("frame1", cv2.WND_PROP_VISIBLE) <1:
        break
    if key== ESC_KEY:
        break
cv2.destroyAllWindows()