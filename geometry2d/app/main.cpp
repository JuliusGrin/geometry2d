#include "geometry2d/geometry.hpp"

#include <iostream>

int main() {
    using namespace geometry2d;

    const Polygon rectangle{{0.0, 0.0}, {4.0, 0.0}, {4.0, 3.0}, {0.0, 3.0}};
    const Segment first{{0.0, 0.0}, {4.0, 4.0}};
    const Segment second{{0.0, 4.0}, {4.0, 0.0}};

    std::cout << "Rectangle area: " << area(rectangle) << '\n';
    std::cout << "Diagonals intersect: " << std::boolalpha
              << segmentsIntersect(first, second) << '\n';
    std::cout << "Point (2, 1) is inside: "
              << (locatePoint(rectangle, {2.0, 1.0}) == PointLocation::Inside) << '\n';
}
