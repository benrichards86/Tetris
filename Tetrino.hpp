#ifndef TETRINO_HPP
#define TETRINO_HPP

#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include "RGBColor.hpp"
#include "TCell.hpp"

namespace tetris {

class Tetrino {
private:
  int x;
  int y;
  int rotation;
  GLuint tetrino_drawlist;
  std::vector<TCell*> vec_rep;
  int cell_mask;
  RGBColor color;

public:
  Tetrino();
  ~Tetrino();

public:
  bool OnLoad(int type, int x_loc, int y_loc);
  void OnLoop();
  void OnRender();
  void OnCleanup();

public:
  void RotateRight();
  void RotateLeft();
  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();

private:
  bool LoadCells(unsigned int cells, RGBColor color_value);

};

}

#endif
