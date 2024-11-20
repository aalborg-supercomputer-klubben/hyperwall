import cv2
from zephyr import Stream
from mss import mss
import numpy as np
import sys
import multiprocessing as mp

# constants and arguments
REMOTE = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"
SOURCE = sys.argv[sys.argv.index("--source-video")+1] if "--source-video" in sys.argv else 0
X, Y = [int(item) for item in (sys.argv[sys.argv.index("--dimensions")+1] if "--dimensions" in sys.argv else "2x2").split("x")]
RES_X, RES_Y = [int(item) for item in (sys.argv[sys.argv.index("--resolution")+1] if "--resolution" in sys.argv else "1920x1080").split("x")]
SCREENSHARE = "--screenshare" in sys.argv
print(f'{X=} {Y=}')


manager = mp.Manager()
class Worker(mp.Process):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.stream = Stream(
            url = f"rtsp://{REMOTE}/frame/{self.x}/{self.y}",
            resolution=(int(RES_X/X), int(RES_Y/Y)),
            fps=60,
            bitrate="2M"
        )
        self.data = manager.list()
        print(self.stream.url)

        super().__init__(target=self.main_loop)

    def main_loop(self):
        while True:
            if len(self.data) == 0:
                continue
            frame = self.data.pop(0)
            x_start = int(len(frame)*(self.x / X))
            x_end = int(len(frame)*((self.x + 1) / X))
            y_start = int(len(frame[0])*(self.y / Y))
            y_end = int(len(frame[0])*((self.y + 1) / Y))
            final_frame = frame[x_start:x_end, y_start:y_end]
            self.stream.send(final_frame)
            break

# main loop

workers:list[Worker] = []

for (x, y) in [(x, y) for x in range(X) for y in range(Y)]:
    workers.append(Worker(x, y))
for worker in workers:
    worker.start()


cap = cv2.VideoCapture(SOURCE)
while True:
    _, frame = cap.read()
    for worker in workers:
        worker.data.append(frame)


