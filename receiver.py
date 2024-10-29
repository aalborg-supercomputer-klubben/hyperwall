import cv2
from zephyr import Client
import numpy as np
import sys

remote = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"

if __name__ == "__main__":
  clients = [Client(url=f"rtsp://localhost:8554/test{i}") for i in range(4)]

  while True:
    for i, client in enumerate(clients):
      ret, frame = client.read()
      #cv2.imshow('frame', frame)

      cv2.imshow(f'frame{i}', frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
      client.release()
      break