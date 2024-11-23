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
./scripts/tmux-ffplay.sh
```
