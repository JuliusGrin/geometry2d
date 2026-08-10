#include "geometry2d/geometry.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace geometry2d {
namespace {

int sign(double value) {
    if (value > kEpsilon) {
        return 1;
    }
    if (value < -kEpsilon) {
        return -1;
    }
    return 0;
}

double orientation(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

void validatePolygon(const Polygon& polygon) {
    if (polygon.size() < 3) {
        throw std::invalid_argument("a polygon must contain at least three vertices");
    }
}

}  // namespace

Vector operator-(Point lhs, Point rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

double dot(Vector lhs, Vector rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double cross(Vector lhs, Vector rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

double distance(Point lhs, Point rhs) {
    const Vector difference = lhs - rhs;
    return std::hypot(difference.x, difference.y);
}

bool almostEqual(double lhs, double rhs, double epsilon) {
    return std::abs(lhs - rhs) <= epsilon;
}

bool pointOnSegment(Point point, Segment segment) {
    if (sign(orientation(segment.start, segment.end, point)) != 0) {
        return false;
    }

    return point.x >= std::min(segment.start.x, segment.end.x) - kEpsilon &&
           point.x <= std::max(segment.start.x, segment.end.x) + kEpsilon &&
           point.y >= std::min(segment.start.y, segment.end.y) - kEpsilon &&
           point.y <= std::max(segment.start.y, segment.end.y) + kEpsilon;
}

bool segmentsIntersect(Segment lhs, Segment rhs) {
    const int o1 = sign(orientation(lhs.start, lhs.end, rhs.start));
    const int o2 = sign(orientation(lhs.start, lhs.end, rhs.end));
    const int o3 = sign(orientation(rhs.start, rhs.end, lhs.start));
    const int o4 = sign(orientation(rhs.start, rhs.end, lhs.end));

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    return (o1 == 0 && pointOnSegment(rhs.start, lhs)) ||
           (o2 == 0 && pointOnSegment(rhs.end, lhs)) ||
           (o3 == 0 && pointOnSegment(lhs.start, rhs)) ||
           (o4 == 0 && pointOnSegment(lhs.end, rhs));
}

double signedArea(const Polygon& polygon) {
    validatePolygon(polygon);

    double twiceArea = 0.0;
    for (std::size_t i = 0; i < polygon.size(); ++i) {
        const Point current = polygon[i];
        const Point next = polygon[(i + 1) % polygon.size()];
        twiceArea += current.x * next.y - current.y * next.x;
    }
    return twiceArea / 2.0;
}

double area(const Polygon& polygon) {
    return std::abs(signedArea(polygon));
}

bool isCounterClockwise(const Polygon& polygon) {
    return signedArea(polygon) > kEpsilon;
}

PointLocation locatePoint(const Polygon& polygon, Point point) {
    validatePolygon(polygon);

    bool inside = false;
    for (std::size_t i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) {
        const Segment edge{polygon[j], polygon[i]};
        if (pointOnSegment(point, edge)) {
            return PointLocation::Boundary;
        }

        const bool crossesHorizontalRay =
            (polygon[i].y > point.y) != (polygon[j].y > point.y);
        if (crossesHorizontalRay) {
            const double intersectionX = polygon[i].x +
                (point.y - polygon[i].y) * (polygon[j].x - polygon[i].x) /
                    (polygon[j].y - polygon[i].y);
            if (intersectionX > point.x) {
                inside = !inside;
            }
        }
    }

    return inside ? PointLocation::Inside : PointLocation::Outside;
}

}  // namespace geometry2d
