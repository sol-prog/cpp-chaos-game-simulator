#pragma once
#include <random>
#include <functional>
#include "geometry.h"

struct ChaosGame {
    static const int max_iterations = 100'000;
    static const int ignore_first_iterations = 10;

    Point2D last_point;
    int last_vertex;
    RegularPolygon polygon;

    std::uniform_int_distribution<int> uniform_dist;
    std::mt19937_64 engine;

    ChaosGame(const RegularPolygon &poly) {
        polygon = poly;

        last_point = polygon.points[0];
        last_vertex = 0;

        std::random_device r;
        std::mt19937_64 eng(r());
        std::uniform_int_distribution<int> distr(0, polygon.nr_edges - 1);
        uniform_dist = distr;
        engine = eng;
    }

    Point2D get_next_point(const std::function<bool (int, int, int)> &func, double ratio = 0.5, int dist = 0) {
        Point2D point;
        bool running = true;
        int remove_iter = 0;
        while(running) {
            int random_vertex = uniform_dist(engine);
            if(func(random_vertex, last_vertex, dist)) {
                point.x = (last_point.x + polygon.points[random_vertex].x) * ratio;
                point.y = (last_point.y + polygon.points[random_vertex].y) * ratio;

                last_vertex = random_vertex;
                last_point = point;
                remove_iter++;
                if(remove_iter >= ignore_first_iterations) {
                    running = false;
                }
            }
        }
        return point;
    }
};