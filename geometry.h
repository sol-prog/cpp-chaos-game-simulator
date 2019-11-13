#pragma once
#include <cmath>

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
