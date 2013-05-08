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
  GLuint tetrino_drawlist;
  std::vector<TCell*> vec_rep;
  int cell_mask;
  RGBColor color;

public:
  int row;
  int column;

public:
  Tetrino();
  ~Tetrino();

public:
  bool OnLoad(int type);
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
  TCell* operator[](int index);

private:
  bool LoadCells(unsigned int cells, RGBColor color_value);

};

}

#endif
