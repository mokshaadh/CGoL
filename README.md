# CGoL
Conway's Game of Life recreation 
Cross-platform, made using [raylib](github.com/raylib) (no changes to library made)

## From source
You need CMake in order to compile from source (unless you decide to install raylib for yourself and copy the main.c file)
In order to compile from source using CMake, clone the directory then run the following:
```sh
mkdir build && cd build && cmake .. && cmake --build . && cd ..
```
Now, to run the compiled executable, run:
```sh
./build/CGoL
```
