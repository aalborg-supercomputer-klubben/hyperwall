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

mapping = {}

cap = cv2.VideoCapture(SOURCE)
while True:
    _, frame = cap.read()
    for (x, y) in [(x, y) for x in range(X) for y in range(Y)]:
        if (x, y) not in mapping:
            mapping[(x, y)] = {
                "stream":Stream(
                    url = f"rtsp://{REMOTE}:8554/frame/{x}/{y}",
                    resolution=(int(RES_X/X), int(RES_Y/Y)),
                    fps=60,
                    bitrate="30M"
                ),
                "sx":int(len(frame)*(x/X)),
                "ex":int(len(frame)*((1+x)/X)),
                "sy":int(len(frame[0])*(y/Y)),
                "ey":int(len(frame[0])*((1+y)/Y))
            }
        m = mapping[(x, y)]
        final_frame = frame[m["sx"]:m["ex"], m["sy"]:m["ey"]]
        m["stream"].send(final_frame)

    
