#pragma once
#include "Ball.hpp"
#include <vector>

class World;

class Physics {
  public:
    void setWorld(const World* world) {
        world_ = world;
    }
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;

  private:
    mutable const World* world_ = nullptr;
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
