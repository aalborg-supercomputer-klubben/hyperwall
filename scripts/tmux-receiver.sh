#!/usr/bin/env bash
for ((x=0;x<$2;x++)); do
    for ((y=0;y<$3;y++)); do
        tmux new-session -d ./build/Receiver --address $1 ${x}x${y}
    done
done
