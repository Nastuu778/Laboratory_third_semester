#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../model/Document.h"
#include "../view/View.h"

class Controller
{
public:
    Controller();

    void onNewDocument();
    void onImport(const std::string &filename);
    void onExport(const std::string &filename);
    void onAddShape(std::unique_ptr<Shape> shape);
    void onViewDocument() const;
    bool onRemoveShape(size_t index);

private:
    std::unique_ptr<Document> document_;
    // умный указатель на сам документ
};