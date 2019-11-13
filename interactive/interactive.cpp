// Interactive version - this requires the SDL2 backend
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp interactive.cpp `pkg-config --cflags --libs sdl2`

#include <iostream>
#include <vector>

#include "../geometry.h"

#include "backend_sdl2.h"

constexpr int width = 800;
constexpr int height = 800;

int main(int argc, char **argv) {
    Rectangle2D world{-1.08, -1.08, 1.08, 1.08};

    Rectangle2D viewport{0, static_cast<double>(height - 1), static_cast<double>(width - 1), 0};
    backend_sdl2(width, height, world, viewport, 0);
}
