#pragma once

#include <vector>

namespace geometry2d {

constexpr double kEpsilon = 1e-9;

struct Point {
    double x{};
    double y{};
};

struct Vector {
    double x{};
    double y{};
};

struct Segment {
    Point start;
    Point end;
};

using Polygon = std::vector<Point>;

enum class PointLocation {
    Outside,
    Boundary,
    Inside,
};

Vector operator-(Point lhs, Point rhs);
double dot(Vector lhs, Vector rhs);
double cross(Vector lhs, Vector rhs);
double distance(Point lhs, Point rhs);
bool almostEqual(double lhs, double rhs, double epsilon = kEpsilon);
bool pointOnSegment(Point point, Segment segment);
bool segmentsIntersect(Segment lhs, Segment rhs);
double signedArea(const Polygon& polygon);
double area(const Polygon& polygon);
bool isCounterClockwise(const Polygon& polygon);
PointLocation locatePoint(const Polygon& polygon, Point point);

}  // namespace geometry2d
