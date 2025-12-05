#include "../include/model/Document.h"
#include <iostream>

void Document::addShape(std::unique_ptr<Shape> shape)
{
    shapes_.push_back(std::move(shape));
    std::cout << "Added shape to document\n";
}

bool Document::removeShape(size_t index)
{
    if (index >= shapes_.size())
    {
        std::cout << "Invalid index for removal\n";
        return false;
    }
    shapes_.erase(shapes_.begin() + index);
    std::cout << "Removed shape at index " << index << "\n";
    return true;
}

void Document::importFromFile(const std::string &filename)
{
    std::cout << "Imported document from file: " << filename << "\n";
}

void Document::exportToFile(const std::string &filename)
{
    std::cout << "Exported document to file: " << filename << "\n";
}

void Document::clear()
{
    shapes_.clear();
    std::cout << "Document cleared\n";
}

void Document::listShapes() const
{
    if (shapes_.empty())
    {
        std::cout << "Document is empty.\n";
        return;
    }
    std::cout << "Document contains " << shapes_.size() << " shape(s):\n";
    for (size_t i = 0; i < shapes_.size(); ++i)
    {
        std::cout << "  [" << i << "] ";
        shapes_[i]->info(); // ← полиморфный вызов!
    }
}