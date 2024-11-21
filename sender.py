from zephyr import Stream
import numpy as np
import sys

# constants and arguments
REMOTE = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"
SOURCE = sys.argv[sys.argv.index("--source-video")+1] if "--source-video" in sys.argv else 0
X, Y = [int(item) for item in (sys.argv[sys.argv.index("--dimensions")+1] if "--dimensions" in sys.argv else "2x2").split("x")]
RES_X, RES_Y = [int(item) for item in (sys.argv[sys.argv.index("--resolution")+1] if "--resolution" in sys.argv else "1920x1080").split("x")]
BITRATE = sys.argv[sys.argv.index("--bitrate")+1] if "--bitrate" in sys.argv else "40M"
FRAMERATE = int(sys.argv[sys.argv.index("--framerate")+1]) if "--framerate" in sys.argv else 60
SCREENSHARE = "--screenshare" in sys.argv

print(f'{X=} {Y=}')

def main_loop(frame_gen, stop_condition=lambda: True):
    frame = frame_gen()

    mapping = {(x, y): {
        "stream": Stream(
            url = f"rtsp://{REMOTE}:8554/frame/{x}/{y}",
            resolution = (int(RES_X/X), int(RES_Y/Y)),
            fps = FRAMERATE,
            bitrate = BITRATE
        ),
        "sx":int(len(frame)*(x/X)),
        "ex":int(len(frame)*((1+x)/X)),
        "sy":int(len(frame[0])*(y/Y)),
        "ey":int(len(frame[0])*((1+y)/Y))
    } for x in range(X) for y in range(Y)}

    while stop_condition():
        if frame is None:
            break
        for m in [mapping[(x, y)] for x in range(X) for y in range(Y)]:
            final_frame = frame[m["sx"]:m["ex"], m["sy"]:m["ey"]]
            m["stream"].send(final_frame)
        frame = frame_gen()

if SCREENSHARE:
    import mss
    with mss.mss() as sct:
        capture = lambda: np.array(sct.grab({"top":0, "left":0, "width":RES_X, "height":RES_Y}))
        main_loop(capture)
else:
    import cv2
    cap = cv2.VideoCapture(SOURCE)
    capture = lambda: cap.read()[1]
    main_loop(capture)
