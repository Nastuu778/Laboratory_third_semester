#pragma once
#include "Color.h"
#include "Painter.h"
#include "Point.h"

class Dust {
  private:
    Point dustVelocity;
    Point dustCenter;
    Color dustColor;
    double dustRadius;
    double lifeTimer;
    double initialLifeTime;

  public:
    Dust(Point center, double radius, Point velocity, Color color,
         double lifetimer);
    void update(double tick);
    bool isDead() const;
    void draw(Painter& painter) const;
};