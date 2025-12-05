#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(int id) : id_(id) {} // конструктор
    void info() const override  // реализация полиморфного интерфейса
    {
        //(override) - проверяет переопределён ли метод
        std::cout << "Circle #" << id_ << "\n";
    }

private:
    int id_; // id фигуры
};