#!/usr/bin/env bash

for ((x=0;x<$2;x++)); do
  for ((y=0;y<$3;y++)); do
    tmux new-session -d ffplay rtsp://$1:8554/frame/$x/$y
  done
done
