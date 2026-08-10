#include "geometry2d/geometry.hpp"

#include <cstdlib>
#include <iostream>
#include <string_view>

namespace {

int failures = 0;

void expect(bool condition, std::string_view testName) {
    if (!condition) {
        std::cerr << "FAILED: " << testName << '\n';
        ++failures;
    }
}

}  // namespace

int main() {
    using namespace geometry2d;

    expect(almostEqual(distance({0, 0}, {3, 4}), 5.0), "distance");
    expect(almostEqual(dot({1, 2}, {3, 4}), 11.0), "dot product");
    expect(almostEqual(cross({1, 0}, {0, 1}), 1.0), "cross product");

    expect(segmentsIntersect({{0, 0}, {4, 4}}, {{0, 4}, {4, 0}}),
           "crossing segments");
    expect(segmentsIntersect({{0, 0}, {2, 0}}, {{2, 0}, {3, 1}}),
           "segments touching at endpoint");
    expect(segmentsIntersect({{0, 0}, {4, 0}}, {{2, 0}, {6, 0}}),
           "overlapping collinear segments");
    expect(!segmentsIntersect({{0, 0}, {1, 0}}, {{2, 0}, {3, 0}}),
           "separate segments");

    const Polygon rectangle{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    expect(almostEqual(area(rectangle), 12.0), "polygon area");
    expect(isCounterClockwise(rectangle), "polygon orientation");
    expect(locatePoint(rectangle, {2, 1}) == PointLocation::Inside, "point inside");
    expect(locatePoint(rectangle, {4, 2}) == PointLocation::Boundary, "point on boundary");
    expect(locatePoint(rectangle, {5, 2}) == PointLocation::Outside, "point outside");

    const Polygon concave{{0, 0}, {4, 0}, {4, 4}, {2, 2}, {0, 4}};
    expect(locatePoint(concave, {1, 1}) == PointLocation::Inside,
           "point inside concave polygon");
    expect(locatePoint(concave, {2, 3}) == PointLocation::Outside,
           "point in concavity");

    if (failures == 0) {
        std::cout << "All tests passed\n";
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
