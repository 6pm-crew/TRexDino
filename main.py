import window
import cv2
import time
import win32gui
import numpy as np
from DQNTrainer import DQNTrainer  


print("running")
ESC_KEY=27
FRAME_RATE = 90
SLEEP_TIME = 1/FRAME_RATE

capture = window.WindowCapture("T-Rex Game",FRAME_RATE)
trainer = DQNTrainer()


while True:
    start=time.time()
    frame = capture.screenshot()
    cv2.imshow("frame1",frame)
    print(trainer.isGameOver(frame))
    delta= time.time()-start
    key= cv2.waitKey(1) & 0xFF
    if cv2.getWindowProperty("frame1", cv2.WND_PROP_VISIBLE) <1:
        break
    if key== ESC_KEY:
        break
cv2.destroyAllWindows()