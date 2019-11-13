#include "backend_bmp.h"
#include "cpp-bmp-images/BMP.h"

static std::vector<Point2D> points_to_viewport(int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points) {
    std::vector<Point2D> p(points.size());
    Rectangle2D viewport{0, 0, static_cast<double>(width), static_cast<double>(height)};
    Window_to_Viewport wv{world, viewport};

    for(size_t i = 0; i < points.size(); ++i) {
        p[i] = wv.mapping(points[i]);
    }
    return p;
}

void backend_bmp(const char *file_name, int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points) {
	BMP bmp(width, height, false);
    bmp.fill_region(0, 0, width, height, 255, 255, 255, 255);

    std::vector<Point2D> p = points_to_viewport(width, height, world, points);

    for(size_t i = 0; i < p.size(); ++i) {
        bmp.fill_region(p[i].x, p[i].y, 1, 1, 0, 0, 0, 255);
    }

	bmp.write(file_name);
}
