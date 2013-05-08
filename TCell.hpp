#ifndef TCELL_HPP
#define TCELL_HPP

#include "RGBColor.hpp"

namespace tetris {

// Defines a single cell. Makes up tetrino pieces.
class TCell {
public:
  int row;   // row and column of cell within tetrino
  int column;

private:
  RGBColor color;

public:
  TCell();
  ~TCell();

public:
  bool OnLoad(int x_loc, int y_loc, RGBColor color);
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

}

#endif
