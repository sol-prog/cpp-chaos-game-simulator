// Interactive version - this requires that you have the SDL2 library installed
// Use the left/right arrow keys to navigate back and forth in the available selections

// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp interactive.cpp `pkg-config --cflags --libs sdl2`
// g++ -std=c++17 -Wall -pedantic backend_sdl2.cpp interactive.cpp `pkg-config --cflags --libs sdl2`
// cl /std:c++17 /W3 /permissive- /EHsc backend_sdl2.cpp interactive.cpp /Fe:interactive.exe


#include <iostream>
#include <vector>

#include "../geometry.h"

#include "backend_sdl2.h"

constexpr int width = 800;
constexpr int height = 800;

int main(int argc, char **argv) {
    Rectangle2D world{-1.08, -1.08, 1.08, 1.08};

    Rectangle2D screen_space{0, static_cast<double>(height - 1), static_cast<double>(width - 1), 0};
    backend_sdl2(width, height, world, screen_space, 0);
}
