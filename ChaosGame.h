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

int generate_points(std::vector<Point2D> &points, int selection = 0) {
    // wrap the values for selection values larger than the number of implemented selections
    if(selection > 14) {
        selection = 0;
    }

    // default selection = 0 settings
    int nr_edges = 3;
    double ratio = 0.5;
    int distance = 0;
    std::function<bool (int, int, int)> func = [] (int random_vertex, int last_vertex, int dist) -> bool {return true;};

    if(selection == 1) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 4;
        ratio = 0.5;
        distance = 0;
    }
    if(selection == 2) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 4;
        ratio = 0.5;
        distance = 2;
    }
    if(selection == 3) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 5;
    }
    if(selection == 4) {
        nr_edges = 7;
        ratio = 0.4;
    }
    if(selection == 5) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 7;
        ratio = 0.4;
        distance = 3;
    }
    if(selection == 6) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 6;
        ratio = 0.4;
        distance = 3;
    }
    if(selection == 7) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 6;
        ratio = 0.375;
        distance = 0;
    }
    if(selection == 8) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 6;
        ratio = 0.5;
        distance = 0;
    }
    if(selection == 9) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 8;
        ratio = 0.4;
        distance = 0;
    }
    if(selection == 10) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 10;
        ratio = 0.375;
        distance = 1;
    }
    if(selection == 11) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 10;
        ratio = 0.375;
        distance = 2;
    }
    if(selection == 12) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 10;
        ratio = 0.375;
        distance = 3;
    }
    if(selection == 13) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 10;
        ratio = 0.375;
        distance = 4;
    }
    if(selection == 14) {
        func = [] (int random_vertex, int last_vertex, int dist) -> bool {return (std::abs(random_vertex - last_vertex) != dist);};
        nr_edges = 10;
        ratio = 0.375;
        distance = 5;
    }

    RegularPolygon polygon(nr_edges);
    ChaosGame chaos(polygon);

    for(auto &p : points) {
        p = chaos.get_next_point(func, ratio, distance);
    }

    return selection;
}
