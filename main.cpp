// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp main.cpp
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp main.cpp `pkg-config --cflags --libs sdl2`

#define USE_SDL2_BACKEND 1

#include <iostream>
#include <vector>

#include "geometry.h"
#include "ChaosGame.h"

#ifdef USE_SDL2_BACKEND
    #include "backend_sdl2.h"
#else
    #include "backend_bmp.h"
#endif

constexpr int width = 800;
constexpr int height = 800;

int main(int argc, char **argv) {
    Rectangle2D world{-1.08, -1.08, 1.08, 1.08};

    int nr_edges = 3;
    double ratio = 0.5;
    int distance = 0;

    RegularPolygon pp(nr_edges);
    ChaosGame chaos(pp);
    std::vector<Point2D> points(ChaosGame::max_iterations);

    //std::function<bool (int, int, int)> func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
    std::function<bool (int, int, int)> func = [] (int random_vertex, int last_vertex, int dist) -> bool {return true;};
    for(auto &p : points) {
        p = chaos.get_next_point(func, ratio, distance);
    }

#ifdef USE_SDL2_BACKEND
    Rectangle2D viewport{0, static_cast<double>(height - 1), static_cast<double>(width - 1), 0};
    backend_sdl2(width, height, world, viewport, points, 0);
#else
    Rectangle2D viewport{0, 0, static_cast<double>(width - 1), static_cast<double>(height - 1)};
    backend_bmp("chaos.bmp", width, height, world, viewport, points, 0);
#endif
}
