#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP

class RGBColor {
public:
  int red;
  int green;
  int blue;
  
  RGBColor();
  ~RGBColor();
  RGBColor& operator=(RGBColor color);
};

#endif
