#pragma once

#include <vector>

#include "point.h"

// Find the closest pair of points from given points.
std::pair<Point, Point> closest_pair(const std::vector<Point> &points);

std::pair<Point, Point> brute_force(const std::vector<Point> &points);
std::pair<Point, Point> divide_and_conquer(std::vector<Point> &points);