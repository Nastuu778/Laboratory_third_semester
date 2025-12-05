#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Shape.h"

class Document
{
public:
    void addShape(std::unique_ptr<Shape> shape);
    bool removeShape(size_t index);
    void importFromFile(const std::string &filename);
    void exportToFile(const std::string &filename);
    void listShapes() const;
    void clear();

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    // вектор из умных указателей указывающих на фигуры
};