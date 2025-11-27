#pragma once
#include <istream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

    friend std::istream&
    operator>>(std::istream& is,
               Color& c); // чтобы могла получить доступ к приватным r, g, b

  private:
    double r{};
    double g{};
    double b{};
};
