#!/usr/bin/env bash

tmux new-session -d "ffplay udp://localhost:8500 -x 960 -y 540 -autoexit && sleep 10"
tmux split -h ffplay udp://localhost:8510 -x 960 -y 540 -autoexit

tmux split ffplay udp://localhost:8501 -x 960 -y 540 -autoexit
tmux select-pane -L
tmux split ffplay udp://localhost:8511 -x 960 -y 540 -autoexit
