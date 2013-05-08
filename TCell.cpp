#include <GL/glu.h>
#include <GL/gl.h>
#include "RGBColor.hpp"
#include "TCell.hpp"

using namespace tetris;

TCell::TCell() {
  row = column = 0;
  color.red = color.green = color.blue = 255;
}

TCell::~TCell() {
}

bool TCell::OnLoad(int column_loc, int row_loc, RGBColor base_color) {
  column = column_loc;
  row = row_loc;
  color = base_color;
  return true;
}

void TCell::OnLoop() {
}

void TCell::OnRender() {
  glPushMatrix();
  glColor3ub(color.red, color.green, color.blue);

  glBegin(GL_QUADS);
  glVertex2i(20 * column - 40, 20 * row - 40);
  glVertex2i(20 * column - 20, 20 * row - 40);
  glVertex2i(20 * column - 20, 20 * row - 20);
  glVertex2i(20 * column - 40, 20 * row - 20);
  glEnd();
  
#ifdef DEBUG
  glColor3ub(255, 255, 255);
  glBegin(GL_LINES);
  glVertex2i(20 * column - 30, 20 * row - 40);
  glVertex2i(20 * column - 30, 20 * row - 30);
  glEnd();
#endif
  glPopMatrix();
}

void TCell::OnCleanup() {
}
