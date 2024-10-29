import cv2
from zephyr import Client
import numpy as np
import sys

remote = sys.argv[sys.argv.index("--remote")+1] if "--remote" in sys.argv else "localhost:8554"

client_number = sys.argv[sys.argv.index("--number")+1] if "--number" in sys.argv else 0

all_frames = int(sys.argv[sys.argv.index("--all")+1]) if "--all" in sys.argv else False


def receiver(client:Client, n):
  _, frame = client.read()
  #cv2.imshow('frame', frame)
  cv2.imshow(f'frame {n}', frame)



if __name__ == "__main__":
  if all_frames:
    clients = [Client(url=f"rtsp://{remote}/frame{i}") for i in range(all_frames)]
    while True:
      for n, client in enumerate(clients):
        receiver(client, n)
      
      if cv2.waitKey(1) & 0xFF == ord("q"):
        client.release()
        break
  else:
    client = Client(url=f"rtsp://{remote}/frame{client_number}")
    while True:
      receiver(client, client_number)

      if cv2.waitKey(1) & 0xFF == ord("q"):
        client.release()
        break