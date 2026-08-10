# Geometry2D

Небольшой проект на C++17 с базовыми алгоритмами для двумерной геометрии:

- пересечение отрезков;
- площадь и ориентация многоугольника;
- положение точки относительно многоугольника.

## Сборка

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/geometry_demo
```
