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

    double width() const {
        return std::abs(right - left);
    }

    double height() const {
        return std::abs(top - bottom);
    }
};

struct RegularPolygon {
    int nr_edges = 3;
    double radius = 1.0;
    double start_angle = 90.0;
    double angle = 120.0;
    std::vector<Point2D> points;

    RegularPolygon() {
        points.resize(nr_edges);
        init_points();
    }

    RegularPolygon(int nr_edges, double radius = 1.0) : nr_edges{nr_edges}, radius{radius} {
        points.resize(nr_edges);
        angle = 360.0 / nr_edges;
        if(nr_edges % 2 == 0) {
            start_angle = 0.0;
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
    x_viewport = A * x_window + C
    y_viewport = B * y_window + D
where:
    A = (V.right - V.left)/(W.right - W.left)
    B = (V.top - V.bottom)/(W.top - W.bottom)
    C = V.left - A * W.left
    D = V.bottom - B * W.bottom

Note: The mapping holds even when the viewport has the Y axis pointing down (in which case top = 0 and bottom = height).
*/
struct Window_to_Viewport {
    double A;
    double B;
    double C;
    double D;

    Window_to_Viewport(const Rectangle2D &window, const Rectangle2D &viewport) {
        A = (viewport.right - viewport.left) / (window.right - window.left);
        B = (viewport.top - viewport.bottom) / (window.top - window.bottom);
        C = viewport.left - A * window.left;
        D = viewport.bottom - B * window.bottom;
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
