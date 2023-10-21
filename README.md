# CGoL
[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) recreation. Cross-platform, made using [raylib](https://github.com/raysan5/raylib) (no changes to library made)

![Gosper glider gun](https://github.com/mokshaadh/CGoL/assets/72827902/f19eaaaa-4203-4a6c-b819-29c11b24220b)

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

