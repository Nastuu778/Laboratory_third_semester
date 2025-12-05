#include "../include/controller/Controller.h"
#include <iostream>

Controller::Controller() : document_(std::make_unique<Document>()) {}

void Controller::onNewDocument()
{
    document_ = std::make_unique<Document>();
    std::cout << "Created new document\n";
}

void Controller::onImport(const std::string &filename)
{
    document_->importFromFile(filename);
}

void Controller::onExport(const std::string &filename)
{
    document_->exportToFile(filename);
}

void Controller::onAddShape(std::unique_ptr<Shape> shape)
{
    document_->addShape(std::move(shape)); // передаём владение из контроллера к документу
}

bool Controller::onRemoveShape(size_t index)
{
    return document_->removeShape(index);
}

void Controller::onViewDocument() const
{
    document_->listShapes();
}