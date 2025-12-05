#pragma once
#include <iostream>
#include <memory>

class Shape // Shape — базовый класс, от которого наследуются Rectangle, Circle
{
public:
    virtual ~Shape() = default;    // деконструктор
    virtual void info() const = 0; // полиморфизм, его реализуют наследники
};