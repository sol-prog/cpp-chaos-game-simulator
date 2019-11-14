Support for [C++ Implementing a Chaos Game simulator](https://solarianprogrammer.com/2019/11/13/cpp-chaos-game-simulator/)

How to use:

```
git clone --recursive https://github.com/sol-prog/cpp-chaos-game-simulator
cd cpp-chaos-game-simulator
```

# Build on Linux, macOS, WSL or Windows with MSYS2:

* If you have SDL2 (for the interactive version use the Left/Right arrow keys):

```
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp main.cpp `pkg-config --cflags --libs sdl2`
./a.out 3
cd interactive
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp main.cpp `pkg-config --cflags --libs sdl2`
./a.out
```

* If you don't have SDL2 installed open *main.cpp*, *backend_test.cpp*, *polygons_test.cpp* and comment the *USE_SDL2_BACKEND* line!!!

```
clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp main.cpp
./a.out 3
```

# Build on Windows with MSVS:

* If you have SDL2 installed globally with vcpkg (for the interactive version use the Left/Right arrow keys):

```
cl /std:c++17 /W3 /permissive- /EHsc backend_sdl2.cpp main.cpp /Fe:main.exe
main.exe 3
cd interactive
cl /std:c++17 /W3 /permissive- /EHsc backend_sdl2.cpp main.cpp /Fe:main.exe
main.exe
```

* If you don't have SDL2 installed open *main.cpp*, *backend_test.cpp*, *polygons_test.cpp* and comment the *USE_SDL2_BACKEND* line!!!

```
cl /std:c++17 /W3 /permissive- /EHsc backend_bmp.cpp main.cpp /Fe:main.exe
main.exe 3
```
