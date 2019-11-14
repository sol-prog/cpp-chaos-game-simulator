#pragma once
#include <cmath>
#include <vector>

struct Point2D {
    double x;
    double y;
};

struct Rectangle2D {
    double left;
    double bottom;
    double right;
    double top;

    Rectangle2D(double left, double bottom, double right, double top) : left{left}, bottom{bottom}, right{right}, top{top} {}
};

struct RegularPolygon {
    int nr_edges = 3;
    double radius = 1.0;
    double start_angle = 90.0;
    double angle = 120.0;
    std::vector<Point2D> points;

    // default create an equilateral triangle
    RegularPolygon() {
        points.resize(nr_edges);
        init_points();
    }

    RegularPolygon(int nr_edges, double radius = 1.0) : nr_edges{nr_edges}, radius{radius} {
        points.resize(nr_edges);
        angle = 360.0 / nr_edges;
        // We change the start_angle in order to have the lower edge of every polygon parallel with the horizontal axis
        if(nr_edges % 2 == 0) {
            start_angle = 0.0;
            // For a square keep the square edges parallel with the windows edges
            if(nr_edges == 4) {
                start_angle = 45.0;
            }
        }
        init_points();
    }

    void init_points() {
        const double PI = acos(-1.0);   // in C++20 and up replace with std::pi from <numbers>
        const double deg_rad = PI/180.0;

        double current_angle = start_angle * deg_rad;
        double min_y = 2.0;
        for(int i = 0; i < nr_edges; ++i) {
            points[i].x = radius * cos(current_angle);
            points[i].y = radius * sin(current_angle);
            if(min_y > points[i].y) min_y = points[i].y;
            current_angle += angle * deg_rad;
        }

        // Center the points vertically
        double offset = (2.0 - (1.0 - min_y))/2.0;
        if(nr_edges % 2 != 0) {
            for(int i = 0; i < nr_edges; ++i) {
                points[i].y -= offset;
            }
        }
    }
};

/*
2D window(real space or the "world") to viewport(screen/canvas space) mapping:
    x_screen_space = A * x_world + C
    y_screen_space = B * y_world + D
where:
    A = (S.right - S.left)/(W.right - W.left)
    B = (S.top - S.bottom)/(W.top - W.bottom)
    C = S.left - A * W.left
    D = S.bottom - B * W.bottom

Note: The mapping holds even when the screen space has the Y axis pointing down (in which case top = 0 and bottom = height).
*/
struct World_to_ScreenSpace {
    double A;
    double B;
    double C;
    double D;

    World_to_ScreenSpace(const Rectangle2D &world, const Rectangle2D &screen_space) {
        A = (screen_space.right - screen_space.left) / (world.right - world.left);
        B = (screen_space.top - screen_space.bottom) / (world.top - world.bottom);
        C = screen_space.left - A * world.left;
        D = screen_space.bottom - B * world.bottom;
    }

    Point2D mapping(const Point2D p) const {
        Point2D sp;
        sp.x = A * p.x + C;
        sp.y = B * p.y + D;
        return sp;
    }

    Point2D mapping(double x, double y) const {
        Point2D sp;
        sp.x = A * x + C;
        sp.y = B * y + D;
        return sp;
    }
};
