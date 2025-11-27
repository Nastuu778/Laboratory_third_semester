// Dust.cpp
#include "Dust.hpp"
#include "Painter.h"
#include <cmath>
#include <random>

Dust::Dust(Point position, Point velocity, double lifetime, Color color)
    : position(position), velocity(velocity), lifetime(lifetime), color(color) {
}

void Dust::update(double dt) {
    position = position + velocity * dt;
    lifetime -= dt;
}

bool Dust::isAlive() const {
    return lifetime > 0;
}

void Dust::draw(Painter& painter) const {
    // СДЕЛАЕМ ПЫЛЬ ЯРКО-КРАСНОЙ, БОЛЬШОЙ И ХОРОШО ВИДНОЙ
    painter.draw(position, 8.0, Color{1.0, 0.0, 0.0}); // радиус 8, красный
}