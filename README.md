# Geometry2D

A small C++17 library that implements basic algorithms of computational geometry.
It was created as a compact code sample: the focus is on readable interfaces,
edge cases and algorithmic reasoning rather than on a large application.

## Features

- points, vectors, segments and polygons;
- dot product, cross product and Euclidean distance;
- segment intersection, including touching and collinear cases;
- signed and absolute polygon area;
- polygon orientation;
- point-in-polygon classification: inside, outside or on the boundary;
- tests with no third-party dependencies.

## Build and run

Requirements: a C++17 compiler and CMake 3.16 or newer.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/geometry_demo
```

## Algorithms

### Segment intersection

The orientation of three points is determined by the sign of a 2D cross
product. Two segments intersect when their endpoints have opposite orientations
relative to the other segment. Zero-orientation cases are checked separately to
handle touching and overlapping collinear segments. Time complexity is `O(1)`.

### Polygon area

The shoelace formula sums cross products of neighboring vertices. Its sign also
shows vertex order: positive means counter-clockwise. Time complexity is `O(n)`
and extra space is `O(1)`.

### Point in polygon

The ray-casting algorithm sends a horizontal ray from the point and toggles the
result at every polygon-edge crossing. A separate boundary check makes the
classification explicit and avoids ambiguity for points on an edge. Time
complexity is `O(n)` and extra space is `O(1)`.

## Numerical considerations

Calculations use `double`. Results that should be zero are compared with
`kEpsilon = 1e-9` to reduce errors caused by floating-point representation.
For very large coordinates or safety-critical geometry, a scale-aware tolerance
or exact arithmetic would be more appropriate.

## Project structure

```text
include/geometry2d/geometry.hpp  public interface
src/geometry.cpp                 implementation
app/main.cpp                     usage example
tests/geometry_tests.cpp         test cases
```

## Possible extensions

- validation of self-intersecting polygons;
- convex hull construction;
- distance from a point to a segment;
- property-based and randomized tests.
