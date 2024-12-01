#!/usr/bin/env bash

while true; do
    ffplay rtsp://${1}:8554/frame/${2}/${3} -fs -autoexit -window_title "frame-${2}x${3}"
    sleep 1
done
