#include "closest_pair.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

std::pair<Point, Point> brute_force(const std::vector<Point> &points) {
  std::pair<Point, Point> result;
  double min_distance = __DBL_MAX__, distance;
  for (int i = 0; i < points.size(); ++i) {
    for (int j = 0; j < points.size(); ++j) {
      if (i != j) {
        distance = points[i].distance(points[j]);
        if (distance <= min_distance) {
          min_distance = distance;
          result = std::make_pair(points[i], points[j]);
        }
      }
    }
  }
  return result;
}

bool cmpx(Point a, Point b) { return a.x < b.x; }
bool cmpy(Point a, Point b) { return a.y < b.y; }

double dist(std::pair<Point, Point> p) { return p.first.distance(p.second); }

std::pair<Point, Point> closest_pair_between(std::vector<Point> PLeft,
                                             std::vector<Point> PRight,
                                             double d) {
  std::pair<Point, Point> result;
  double Xm = (PLeft[PLeft.size() - 1].x + PRight[0].x) / 2;
  std::vector<Point> PStripe;
  for (Point i : PLeft)
    if (abs(i.x - Xm) < d) PStripe.push_back(i);
  for (Point i : PRight)
    if (abs(i.x - Xm) < d) PStripe.push_back(i);
  std::sort(PStripe.begin(), PStripe.end(), cmpy);
  double min_distance = __DBL_MAX__, distance;
  for (int i = 0; i < PStripe.size() - 1; ++i) {
    for (int j = i + 1;
         j < PStripe.size() && abs(PStripe[i].y - PStripe[j].y) < d; ++j) {
      distance = PStripe[i].distance(PStripe[j]);
      if (distance < min_distance) {
        min_distance = distance;
        result = std::make_pair(PStripe[i], PStripe[j]);
      }
    }
  }
  return result;
}

std::pair<Point, Point> divide_and_conquer(std::vector<Point> &points) {
  std::pair<Point, Point> result;
  if (points.size() <= 3)
    result = brute_force(points);
  else {
    std::sort(points.begin(), points.end(), cmpx);
    std::vector<Point> PLeft(points.size() / 2),
        PRight(points.size() - (points.size() / 2));
    for (int i = 0; i < points.size(); ++i) {
      if (i < points.size() / 2)
        PLeft[i] = points[i];
      else
        PRight[i - points.size() / 2] = points[i];
    }
    std::pair<Point, Point> pl = divide_and_conquer(PLeft),
                            pr = divide_and_conquer(PRight);
    double d = std::min(dist(pl), dist(pr));
    std::pair<Point, Point> pb = closest_pair_between(PLeft, PRight, d);
    double m = std::min(d, dist(pb));
    if (dist(pl) == m)
      result = pl;
    else if (dist(pr) == m)
      result = pr;
    else
      result = pb;
  }
  return result;
}

std::pair<Point, Point> closest_pair(const std::vector<Point> &points) {
  // Return the closest pair of points from given points.
  // Order of points in the result doesn't matter.
  // If there are fewer than 2 points, throw an exception.

  if (points.size() < 2) {
    throw std::invalid_argument("Not enough points");
  }

  std::vector<Point> cpoints = points;
  // Your implementation here.
  std::pair<Point, Point> result = divide_and_conquer(cpoints);

  return result;
}
