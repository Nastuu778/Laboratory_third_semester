#pragma once

#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
  private:
    Point center_;
    Velocity velocity_;
    double radius_;
    Color color_;
    bool collidable_;

  public:
    // Конструктор — обязателен!
    Ball(Point center, Velocity velocity, double radius, Color color,
         bool collidable = true);

    // Геттеры и сеттеры
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;

    void setCenter(const Point& center);
    Point getCenter() const;

    double getRadius() const;
    double getMass() const;
    bool isCollidable() const {
        return collidable_;
    } // ← очень пригодится в пункте 3

    void draw(Painter& painter) const;
};