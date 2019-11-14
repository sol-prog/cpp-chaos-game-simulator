Support for [C++ Implementing a Chaos Game simulator](https://solarianprogrammer.com/2019/11/13/cpp-chaos-game-simulator/)

How to use:

```
git clone --recursive https://github.com/sol-prog/cpp-chaos-game-simulator
cd cpp-chaos-game-simulator
```

# Build on Linux, macOS, WSL or Windows with MSYS2:

* If you have SDL2 (for the interactive version use the Left/Right arrow keys):

```
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp -DUSE_SDL2_BACKEND main.cpp `pkg-config --cflags --libs sdl2`
./a.out 3
cd interactive
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp main.cpp `pkg-config --cflags --libs sdl2`
./a.out
```

* If you don't have SDL2 installed:

```
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp main.cpp
./a.out 3
```

# Build on Windows with MSVC:

* If you have SDL2 installed globally with vcpkg (for the interactive version use the Left/Right arrow keys). Easieast approach is to create a VS project and add the files to it.

It is also possible to build the programs from the Terminal, but you will need to manually add the SDL2 include path and link with the library.


* If you don't have SDL2 installed. Easieast approach is to create a VS project and add the files to it.

Optionally, you can build the programs from the Terminal with:

```
cl /std:c++17 /W3 /permissive- /EHsc backend_bmp.cpp main.cpp /Fe:main.exe
main.exe 3
```
