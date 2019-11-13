#include <SDL2/SDL.h>
#include "backend_sdl2.h"

static std::vector<SDL_Point> points_to_viewport(int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points) {
    std::vector<SDL_Point> p(points.size());

    Rectangle2D viewport{0, static_cast<double>(height), static_cast<double>(width), 0};
    Window_to_Viewport wv{world, viewport};

    for(size_t i = 0; i < points.size(); ++i) {
        Point2D pp = wv.mapping(points[i]);
        p[i].x = pp.x;
        p[i].y = pp.y;
    }
    return p;
}

void backend_sdl2(int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Chaos Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Convert points to SDL2 window and axis orientation
    std::vector<SDL_Point> p = points_to_viewport(width, height, world, points);

    bool running = true;
    SDL_Event event;
    while(running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_q:
                    running = false;
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoints(renderer, &p[0], p.size());

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}