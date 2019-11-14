#include <SDL2/SDL.h>
#include "backend_sdl2.h"
#include "../ChaosGame.h"
#include <iostream>

static std::vector<SDL_Point> points_to_screen_space(int width, int height, const Rectangle2D &world, const Rectangle2D &screen_space, const std::vector<Point2D> &points) {
    std::vector<SDL_Point> p(points.size());

    World_to_ScreenSpace wssp{world, screen_space};

    for(size_t i = 0; i < points.size(); ++i) {
        Point2D pp = wssp.mapping(points[i]);
        p[i].x = pp.x;
        p[i].y = pp.y;
    }
    return p;
}

static void drawPointWithSize(SDL_Renderer *renderer, int width, int height, const SDL_Point &p, int radius) {
    int radius2 = radius * radius;

    int xmin = (p.x - radius) <= 0 ? 0 : (p.x - radius);
    int xmax = (p.x + radius) >= width ? width - 1 : (p.x + radius);

    int ymin = (p.y - radius) <= 0 ? 0 : (p.y - radius);
    int ymax = (p.y + radius) >= height ? height - 1 : (p.y + radius);

    for(int j = ymin; j <= ymax; ++j) {
        for(int i = xmin; i <= xmax; ++i) {
            int dist = (i - p.x) * (i - p.x) + (j - p.y) * (j - p.y);
            if(dist <= radius2) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void backend_sdl2(int width, int height, const Rectangle2D &world, const Rectangle2D &screen_space, int point_radius) {
    std::vector<Point2D> points(ChaosGame::max_iterations);

    // Use the default selection value
    int selection = 0;
    generate_points(points, selection);

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Chaos Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Convert points to SDL2 window and axis orientation
    std::vector<SDL_Point> p = points_to_screen_space(width, height, world, screen_space, points);

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

                    case SDLK_RIGHT:
                    case SDLK_n:
                    selection++;
                    selection = generate_points(points, selection);
                    p = points_to_screen_space(width, height, world, screen_space, points);
                    break;

                    case SDLK_LEFT:
                    case SDLK_l:
                    if(selection > 0) selection--;
                    selection = generate_points(points, selection);
                    p = points_to_screen_space(width, height, world, screen_space, points);
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        if(point_radius == 0) {
            SDL_RenderDrawPoints(renderer, &p[0], p.size());
        } else {
            for(const SDL_Point &e : p) {
                drawPointWithSize(renderer, width, height, e, point_radius);
            }
        }

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}