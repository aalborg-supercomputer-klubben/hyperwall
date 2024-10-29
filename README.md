# asck hyperwall
hyperwall project for asck

setup consists of a rtsp server, a server sending video and a receiver (e.g. vlc or ffplay)
## setup
* run Docker image of rtsp server:

`docker run --rm -it --network=host bluenviron/mediamtx:latest`
* run sender:

`python sender.py --video-source file.mp4 --remote localhost:8554`
* run receiver:

`python receiver.py --remote localhost:8554`
* or run ffplay:
`ffplay rtsp://localhost:8554/frame0`

`ffplay rtsp://localhost:8554/frame1`

`ffplay rtsp://localhost:8554/frame2`

`ffplay rtsp://localhost:8554/frame3`