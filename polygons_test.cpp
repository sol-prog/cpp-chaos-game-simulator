// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp polygons_test.cpp
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp polygons_test.cpp `pkg-config --cflags --libs sdl2`

// #define USE_SDL2_BACKEND

#include <iostream>
#include <vector>

#include "geometry.h"

#ifdef USE_SDL2_BACKEND
    #include "backend_sdl2.h"
#else
    #include "backend_bmp.h"
#endif

constexpr int width = 800;
constexpr int height = 800;

int main(int argc, char **argv) {
    Rectangle2D world{-1.08, -1.08, 1.08, 1.08};
    RegularPolygon polygon(8);

#ifdef USE_SDL2_BACKEND
    Rectangle2D screen_space{0, static_cast<double>(height - 1), static_cast<double>(width - 1), 0};
    backend_sdl2(width, height, world, screen_space, polygon.points, 5);
#else
    Rectangle2D screen_space{0, 0, static_cast<double>(width - 1), static_cast<double>(height - 1)};
    backend_bmp("chaos.bmp", width, height, world, screen_space, polygon.points, 5);
#endif
}
