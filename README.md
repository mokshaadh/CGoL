# CGoL
Conway's Game of Life recreation [(see wikipedia about game)](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). Cross-platform, made using [raylib](https://github.com/raysan5/raylib) (no changes to library made)

## Install
Check the [releases](https://github.com/mokshaadh/CGoL/releases) for binary releases. If your OS is not targetted, please compile from source

## From source
In order to compile from source using [CMake](https://github.com/Kitware/CMake), clone the directory then run the following:
```sh
mkdir build && cd build && cmake .. && cmake --build . && cd ..
```
Now, to run the compiled executable, run:
```sh
./build/CGoL
```
