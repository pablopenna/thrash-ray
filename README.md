# Thrash Ray


## Build
(First time only) Install raylib required libraries or do the next step and install the libraries pointed out during compilation.
https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux

```sh
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```


Setup the build system.
```sh
cmake -S . -B build
cmake --build build
```

## Notes

### \[Linux\] Force usage of dedicated GPU
Prepend the run command with `__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia`. e.g.
```sh
__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./build/Debug/handmade_thrash_ray
```

https://github.com/raylib-cs/raylib-cs/issues/317


## Resources
* Raylib cheatsheet - https://www.raylib.com/cheatsheet/cheatsheet.html
* CMake setup - https://github.com/raysan5/raylib/wiki/CMake-Build-Options
* Sample project with CMake - https://github.com/SasLuca/raylib-cmake-template

