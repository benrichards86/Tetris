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

RGBColor& RGBColor::operator=(DefaultColors color) {
  switch(color) {
  case WHITE:
    red = green = blue = 255;
    break;
  case RED:
    red = 255;
    green = blue = 0;
    break;
  case ORANGE:
    red = 255;
    green = 127;
    blue = 0;
    break;
  case YELLOW:
    red = green = 255;
    blue = 0;
    break;
  case GREEN:
    red = blue = 0;
    green = 255;
    break;
  case BLUE:
    red = green = 0;
    blue = 255;
    break;
  case VIOLET:
    red = blue = 255;
    green = 0;
    break;
  case BROWN:
    red = 255;
    green = 63;
    blue = 0;
    break;
  case BLACK:
  default:
    red = green = blue = 0;
    break;
  }
}
