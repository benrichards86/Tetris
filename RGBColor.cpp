#include "RGBColor.hpp"

RGBColor::RGBColor() {
  red = green = blue = 0;
}

RGBColor::~RGBColor() {
}

RGBColor& RGBColor::operator=(RGBColor color) {
  red = color.red;
  green = color.green;
  blue = color.blue;
  return *this;
}

