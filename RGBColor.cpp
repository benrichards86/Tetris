#include "RGBColor.hpp"

RGBColor::RGBColor() {
  SetByDefaultColor(_black);
}

RGBColor::RGBColor(DefaultColors color) {
  SetByDefaultColor(color);
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
  SetByDefaultColor(color);
}

void RGBColor::SetByDefaultColor(DefaultColors color) {
  switch(color) {
  case _white:
    red = green = blue = 255;
    break;
  case _red:
    red = 255;
    green = blue = 0;
    break;
  case _orange:
    red = 255;
    green = 127;
    blue = 0;
    break;
  case _yellow:
    red = green = 255;
    blue = 0;
    break;
  case _green:
    red = blue = 0;
    green = 255;
    break;
  case _blue:
    red = green = 0;
    blue = 255;
    break;
  case _violet:
    red = blue = 255;
    green = 0;
    break;
  case _brown:
    red = 255;
    green = 63;
    blue = 0;
    break;
  case _black:
  default:
    red = green = blue = 0;
    break;
  }
}

