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

static void drawPointWithSize(BMP &bmp, int width, int height, const Point2D &p, int radius) {
    int radius2 = radius * radius;

    int xmin = static_cast<int>(p.x - radius) <= 0 ? 0 : static_cast<int>(p.x - radius);
    int xmax = static_cast<int>(p.x + radius) >= width ? width - 1 : static_cast<int>(p.x + radius);

    int ymin = static_cast<int>(p.y - radius) <= 0 ? 0 : static_cast<int>(p.y - radius);
    int ymax = static_cast<int>(p.y + radius) >= height ? height - 1 : static_cast<int>(p.y + radius);

    for(int j = ymin; j <= ymax; ++j) {
        for(int i = xmin; i <= xmax; ++i) {
            int dist = (i - p.x) * (i - p.x) + (j - p.y) * (j - p.y);
            if(dist <= radius2) {
                bmp.fill_region(i, j, 1, 1, 0, 0, 0, 255);
            }
        }
    }
}

void backend_bmp(const char *file_name, int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points, int point_radius) {
	BMP bmp(width, height, false);
    bmp.fill_region(0, 0, width, height, 255, 255, 255, 255);

    std::vector<Point2D> p = points_to_viewport(width, height, world, points);

    for(size_t i = 0; i < p.size(); ++i) {
        drawPointWithSize(bmp, width, height, p[i], point_radius);
    }

	bmp.write(file_name);
}
