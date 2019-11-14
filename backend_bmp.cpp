#include "backend_bmp.h"
#include "cpp-bmp-images/BMP.h"

// Transform/Map/Convert the points elements to the screen space
static std::vector<Point2D> points_to_screen_space(int width, int height, const Rectangle2D &world, const Rectangle2D &screen_space, const std::vector<Point2D> &points) {
    std::vector<Point2D> p(points.size());

    World_to_ScreenSpace wssp{world, screen_space};

    for(size_t i = 0; i < points.size(); ++i) {
        p[i] = wssp.mapping(points[i]);
    }
    return p;
}

// Draw a "crude" circle around the point p
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

void backend_bmp(const char *file_name, int width, int height, const Rectangle2D &world, const Rectangle2D &screen_space, const std::vector<Point2D> &points, int point_radius) {
	BMP bmp(width, height, false);
    bmp.fill_region(0, 0, width, height, 255, 255, 255, 255);

    std::vector<Point2D> p = points_to_screen_space(width, height, world, screen_space, points);

    if(point_radius == 0) {
        for(size_t i = 0; i < p.size(); ++i) {
            bmp.set_pixel(p[i].x, p[i].y, 0, 0, 0, 255);
        }
    } else {
        for(size_t i = 0; i < p.size(); ++i) {
            drawPointWithSize(bmp, width, height, p[i], point_radius);
        }
    }

	bmp.write(file_name);
}
