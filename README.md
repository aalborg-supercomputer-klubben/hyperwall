# Hyperwall

## Dependencies
```
opencv (build)
ffmpeg (runtime)
tmux (optional)
```

## Building
on linux:

```sh
cmake -B build
cmake --build build -j4
```

## running
```sh
./build/sender <args>
# in another shell
./scripts/tmux-ffplay.sh <ip addr>
```

### Screensharing
screensharing is at the moment an exercise in setting up a tcp stream yourself. in a shell do something like:
```sh
ffmpeg -f x11grab -i :0 -vcodec libx264 -f mpegts tcp://127.0.0.1:8600
```
then in another shell, start the hyperwall:
```sh
./build/sender screenshare <args>
```
