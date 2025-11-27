#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include "Physics.h"
#include <vector>

class Painter;

class World {
    std::vector<Dust> dustParticles;

  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);
    void addDust(const Dust& dust); // для Physics.cpp
    void updateDust(double dt);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;
};
