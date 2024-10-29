# asck hyperwall
hyperwall project for asck

setup consists of a rtsp server, a server sending video and a receiver (e.g. vlc)
## setup
* run Docker image of rtsp server:

`docker run --rm -it --network=host bluenviron/mediamtx:latest`
* run sender:

`python sender.py --video-source file.mp4 --remote localhost:8554`
* run receiver:

`python receiver.py --remote localhost:8554`
