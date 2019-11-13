// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp backend_test.cpp
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp backend_test.cpp `pkg-config --cflags --libs sdl2`

//#define USE_SDL2_BACKEND 1

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
    Rectangle2D world{0, 0, 800, 800};
    std::vector<Point2D> points{{0, 0}, {10, 10}, {20, 20}, {30, 30}, {40, 40}, {50, 50}, {60, 60}, {70, 70}, {80, 80}, {90, 90}, {799, 799}};

#ifdef USE_SDL2_BACKEND
    backend_sdl2(width, height, world, points, 7);
#else
    backend_bmp("chaos.bmp", width, height, world, points, 7);
#endif
}
