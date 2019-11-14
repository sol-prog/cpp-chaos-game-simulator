// Usage:  "prog_name selection", where selection is a number from 0 to 14

// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_bmp.cpp main.cpp
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic backend_sdl2.cpp -DUSE_SDL2_BACKEND main.cpp `pkg-config --cflags --libs sdl2`
// g++ -std=c++17 -Wall -pedantic backend_bmp.cpp main.cpp
// g++ -std=c++17 -Wall -pedantic backend_sdl2.cpp -DUSE_SDL2_BACKEND main.cpp `pkg-config --cflags --libs sdl2`
// cl /std:c++17 /W3 /permissive- /EHsc backend_bmp.cpp main.cpp /Fe:main.exe
// cl /std:c++17 /W3 /permissive- /EHsc backend_sdl2.cpp /DUSE_SDL2_BACKEND main.cpp /Fe:main.exe

#include <iostream>
#include <vector>
#include <string>

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

    std::vector<Point2D> points(ChaosGame::max_iterations);

    int selection = 0;
    if(argc >= 2) {
        int sel = std::stoi(argv[1]);
        selection = sel >= 0 ? sel : 0;
    }

    generate_points(points, selection);

#ifdef USE_SDL2_BACKEND
    Rectangle2D screen_space{0, static_cast<double>(height - 1), static_cast<double>(width - 1), 0};
    backend_sdl2(width, height, world, screen_space, points, 0);
#else
    Rectangle2D screen_space{0, 0, static_cast<double>(width - 1), static_cast<double>(height - 1)};
    std::string fname = "chaos_" + std::to_string(selection) + ".bmp";
    backend_bmp(fname.c_str(), width, height, world, screen_space, points, 0);
#endif
}
