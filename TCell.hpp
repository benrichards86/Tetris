#ifndef TCELL_HPP
#define TCELL_HPP

#include "RGBColor.hpp"

namespace tetris {

// Defines a single cell. Makes up tetrino pieces.
class TCell {
private:
  int x;
  int y;
  int rot;
  RGBColor color;

public:
  TCell();
  ~TCell();

public:
  bool OnLoad(int x_loc, int y_loc, int rotation, RGBColor color);
  void OnLoop();
  void OnRender();
  void OnCleanup();

public:
  void SetLocation(int x_loc, int y_loc);
  void RotateRight();
  void RotateLeft();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

};

}

#endif
