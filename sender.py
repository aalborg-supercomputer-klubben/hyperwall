from numpy.lib import split
import cv2
from zephyr import Stream
from mss import mss
import numpy as np
import sys
import multiprocessing as mp

remote = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"

file = sys.argv[sys.argv.index("--source-video")+1] if "--source-video" in sys.argv else 0

y, x = [int(item) for item in (sys.argv[sys.argv.index("--dimensions")+1] if "--dimensions" in sys.argv else "2x2").split("x")]

res_x, res_y = [int(item) for item in (sys.argv[sys.argv.index("--resolution")+1] if "--resolution" in sys.argv else "1920x1080").split("x")]

screenshare = "--screenshare" in sys.argv

print(f'{x=} {y=}')

n = x*y

def make_vertical_frames(frame):
  return np.array_split(frame, x, axis=1)

def get_fixed_index(layer):
  return min([min([len(layer2) for layer2 in layer1]) for layer1 in layer])

def fix_frame_index(layer, index):
  return [[layer2[:index] for layer2 in layer1] for layer1 in layer]

def vertical_split(horizontal_frame):
  vertical_frames = make_vertical_frames(horizontal_frame)
  fixed_index = get_fixed_index(vertical_frames)
  return fix_frame_index(vertical_frames, fixed_index)


urls = [f"rtsp://{remote}/frame{i}" for i in range(n)]
streams = [Stream(
  url=url,
  resolution=(int(res_x/x), int(res_y/y)),
  fps=60,
  bitrate="10M"
) for url in urls]

print("sending to:")
for url in urls: print(url)

manager = mp.Manager()

data_queue = manager.dict({index:manager.list() for index in range(n)})

def worker_process(index):
  stream = streams[index]
  while True:
    if len(data_queue[index]) == 0:
      continue
    fixed_frame = np.array(vertical_split(data_queue[index].pop(0)))[0]
    stream.send(fixed_frame)


processes = [mp.Process(target=worker_process, args=[i]) for i in range(n)]
for process in processes:
    process.start()

cap = cv2.VideoCapture(file)
while True:
  if screenshare:
    with mss() as sct:
      frame = np.array(sct.grab({"top":0, "left":0, "width":1920, "height":1080}))
  else:
    _, frame = cap.read()

  # do horizontal splits
  horizontal_frames = np.array_split(frame, y, axis=0)
  for i, frame in enumerate(horizontal_frames):
    data_queue[i].append(frame)
  # do vertical splits
  #with mp.Pool(4) as p:
    #vertical_frames = [np.array_split(_frame, x, axis=1) for _frame in horizontal_frames]
    # fix indices
    #fixed_index = min([min([min([len(layer3) for layer3 in layer2]) for layer2 in layer1]) for layer1 in vertical_frames])
    #fixed_frames = np.array([[[layer3[:fixed_index] for layer3 in layer2] for layer2 in layer1] for layer1 in vertical_frames])
    #fixed_frames = np.array(p.map(vertical_split, horizontal_frames))
  
  #frames = np.concatenate(fixed_frames)

  #for stream, specific_frame in zip(streams, frames):
    #stream.send(specific_frame)
