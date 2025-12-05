#include <iostream>
#include <memory>
#include "../include/model/Rectangle.h"
#include "../include/model/Circle.h"
#include "../include/controller/Controller.h"

// Это симуляция GUI-обработчиков
int main()
{
    std::cout << "=== Vector Editor (MVC Architecture Demo) ===\n";

    Controller ctrl;

    ctrl.onNewDocument();
    ctrl.onAddShape(std::make_unique<Rectangle>(11));
    ctrl.onAddShape(std::make_unique<Circle>(22));
    ctrl.onRemoveShape(0);
    ctrl.onExport("output.vec");

    std::cout << "Demo finished.\n";
    ctrl.onViewDocument();
    return 0;
}