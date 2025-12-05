#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(int id) : id_(id) {}
    void info() const override
    {
        std::cout << "Rectangle #" << id_ << "\n";
    }

private:
    int id_;
};