#pragma once

#include "Color.h"
#include "Point.h"

class Dust {
  public:
    Point position;
    Point velocity;  // направление и скорость полёта
    double lifetime; // оставшееся время жизни (в секундах)
    Color color;

    Dust(Point position, Point velocity, double lifetime,
         Color color = Color{1.0, 1.0, 1.0});

    void update(double dt); // обновляет позицию и уменьшает lifetime
    bool isAlive() const;   // true, если lifetime > 0
    void draw(class Painter& painter) const;
};