#pragma once

#include <vector>
#include "geometry.h"

void backend_bmp(const char *file_name, int width, int height, const Rectangle2D &world, const std::vector<Point2D> &points, int point_radius);
