#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP

class RGBColor {
  enum DefaultColors {_white, _red, _orange, _yellow, _green, _blue, _violet, _brown, _black};

public:
  int red;
  int green;
  int blue;
  
  RGBColor();
  RGBColor(DefaultColors color);
  ~RGBColor();

  RGBColor& operator=(RGBColor color);
  RGBColor& operator=(DefaultColors color);

private:
  void SetByDefaultColor(DefaultColors color);
  
public:
  static const DefaultColors WHITE = _white;
  static const DefaultColors RED = _red;
  static const DefaultColors ORANGE = _orange;
  static const DefaultColors YELLOW = _yellow;
  static const DefaultColors GREEN = _green;
  static const DefaultColors BLUE = _blue;
  static const DefaultColors VIOLET = _violet;
  static const DefaultColors BROWN = _brown;
  static const DefaultColors BLACK = _black;
};

#endif
