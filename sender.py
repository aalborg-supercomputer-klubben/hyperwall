from numpy.lib import split
import cv2
from zephyr import Stream
from mss import mss
import numpy as np
import sys

remote = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"

file = sys.argv[sys.argv.index("--source-video")+1] if "--source-video" in sys.argv else 0

y, x = [int(item) for item in (sys.argv[sys.argv.index("--dimensions")+1] if "--dimensions" in sys.argv else "2x2").split("x")]

res_x, res_y = [int(item) for item in (sys.argv[sys.argv.index("--resolution")+1] if "--resolution" in sys.argv else "1920x1080").split("x")]

screenshare = "--screenshare" in sys.argv

print(f'{x=} {y=}')

n = x*y

if __name__ == "__main__":
  urls = [f"rtsp://{remote}/frame{i}" for i in range(n)]
  streams = [Stream(
    url=url,
    resolution=(int(res_x/x), int(res_y/y)),
    fps=30,
    bitrate="2M"
  ) for url in urls]

  print("sending to:")
  for url in urls: print(url)
  if not screenshare:
    cap = cv2.VideoCapture(file)
  else:
      sct = mss()
  while True:
    if not screenshare:
      ret, frame = cap.read()
    else:
        frame = np.array(sct.grab({"top":0, "left":0, "width":res_x, "height":res_y}))

    # do horizontal splits
    horizontal_frames = np.array_split(frame, y, axis=0)
    # do vertical splits
    vertical_frames = [np.array_split(_frame, x, axis=1) for _frame in horizontal_frames]
    # fix indices
    fixed_index = min([min([min([len(layer3) for layer3 in layer2]) for layer2 in layer1]) for layer1 in vertical_frames])
    fixed_frames = np.array([[[layer3[:fixed_index] for layer3 in layer2] for layer2 in layer1] for layer1 in vertical_frames])

    frames = np.concatenate(fixed_frames)


    for stream, specific_frame in zip(streams, frames):
      stream.send(specific_frame)
