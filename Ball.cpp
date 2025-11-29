#include "Ball.hpp"
#include <cmath>

Ball::Ball(Point center, Velocity velocity, double radius, Color color,
           bool collidable)
    : center_(center), velocity_(velocity), radius_(radius), color_(color),
      collidable_(collidable) {}

void Ball::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

Velocity Ball::getVelocity() const {
    return velocity_;
}

void Ball::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

void Ball::setCenter(const Point& center) {
    center_ = center;
}

Point Ball::getCenter() const {
    return center_;
}

double Ball::getRadius() const {
    return radius_;
}

double Ball::getMass() const {
    return M_PI * radius_ * radius_;
}