#!/usr/bin/env bash
for ((x=0;x<$2;x++)); do
    for ((y=0;y<$3;y++)); do
        tmux new-session -d ./scripts/ffplay-single.sh $1 $x $y
    done
done
