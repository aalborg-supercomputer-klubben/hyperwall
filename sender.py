import cv2
from zephyr import Stream
import numpy as np
import sys

remote = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"

file = sys.argv[sys.argv.index("--source-video")+1] if "--source-video" in sys.argv else 0

x, y = [int(item) for item in (sys.argv[sys.argv.index("--dimensions")+1] if "--dimensions" in sys.argv else "2x2").split("x")]

if __name__ == "__main__":
  urls = [f"rtsp://{remote}/test{i}" for i in range(4)]
  streams = [Stream(
    url=url,
    resolution=(int(1920/4), int(1080/4)),
    fps=30,
    bitrate="2M"
  ) for url in urls]

  print("sending to:")
  for url in urls: print(url)

  cap = cv2.VideoCapture(file)
  while True:
    ret, frame = cap.read()

    # do horizontal splits
    horizontal_frames = np.array_split(frame, x)
    frames = [np.array_split(frame, y, axis=1) for frame in horizontal_frames]
    for stream, specific_frame in zip(streams, frames):
      stream.send(specific_frame)