#!/usr/bin/env bash

for ((x=0;x<$1;x++)); do
  for ((y=0;y<$2;y++)); do
    tmux new-session -d ./build/Receiver ${x}x${y}
  done
done
